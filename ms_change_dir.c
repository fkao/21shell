/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 14:10:46 by fkao              #+#    #+#             */
/*   Updated: 2017/09/11 11:00:41 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_envar(t_list *lst, char *str)
{
	while (lst)
	{
		if (ft_strnequ((char*)lst->content, str, ft_strlen(str)))
			return ((char*)lst->content + ft_strlen(str));
		lst = lst->next;
	}
	return (NULL);
}

char	*parse_cd_3(char **av, char *old_path)
{
	char	*old;
	char	*new;
	char	*tmp;
	char	*tmp2;

	old = ft_strdup(old_path);
	if (!(tmp = ft_strstr(old, av[1])))
	{
		free(old);
		write(2, RED "cd: string not in pwd: ", 28);
		write(2, av[1], ft_strlen(av[1]));
		write(2, "\n" RESET, 6);
		return (NULL);
	}
	*tmp = '\0';
	tmp = tmp + ft_strlen(av[1]);
	tmp2 = ft_strjoin(old, av[2]);
	new = ft_strjoin(tmp2, tmp);
	free(old);
	free(tmp2);
	return (new);
}

char	*parse_cd_2(char **av, t_list *lstenv)
{
	char	*new;
	char	*tmp;

	if (ft_strequ(av[1], "-") && (tmp = get_envar(lstenv, "OLDPWD=")))
		new = ft_strdup(tmp);
	else if (av[1][0] == '~' && (tmp = get_envar(lstenv, "HOME=")))
		new = ft_strjoin(tmp, av[1] + 1);
	else if (ft_strequ(av[1], "/"))
		new = ft_strdup(av[1]);
	else
		new = ft_strdup(av[1]);
	return (new);
}

char	*parse_cd(int ac, char **av, t_list *lstenv, char *old_path)
{
	char	*new;
	char	*tmp;

	if (ac == 1)
	{
		tmp = get_envar(lstenv, "HOME=");
		new = (tmp) ? ft_strdup(tmp) : ft_strdup("/");
	}
	else if (ac == 2)
		new = parse_cd_2(av, lstenv);
	else if (ac == 3)
		new = parse_cd_3(av, old_path);
	else
	{
		write(2, RED "cd: too many arguments\n" RESET, 33);
		return (NULL);
	}
	return (new);
}

void	ms_change_dir(int ac, char **av, t_list **lstenv)
{
	char	old_path[PATH_MAX];
	char	path[PATH_MAX];
	char	*new;

	getcwd(old_path, PATH_MAX);
	if (!(new = parse_cd(ac, av, *lstenv, old_path)))
		return ;
	if (chdir(new))
	{
		write(2, RED "cd: no such file or directory: ", 36);
		(ac == 2) ? write(2, av[1], ft_strlen(av[1])) :
		write(2, new, ft_strlen(new));
		write(2, "\n" RESET, 6);
		free(new);
		return ;
	}
	else
	{
		if (ac == 3)
			ft_printf("%s\n", new);
		set_env("OLDPWD", old_path, lstenv);
		getcwd(path, PATH_MAX);
		set_env("PWD", path, lstenv);
		free(new);
	}
}
