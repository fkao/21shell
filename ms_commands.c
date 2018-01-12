/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 15:58:07 by fkao              #+#    #+#             */
/*   Updated: 2018/01/12 11:02:04 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static char	**get_path(t_list *lstenv)
{
	char	**path;
	char	**ptr;
	char	*tmp;

	if (!(tmp = get_envar(lstenv, "PATH=")))
		return (NULL);
	path = ft_strsplit(tmp, ':');
	ptr = path;
	while (*ptr)
	{
		tmp = *ptr;
		*ptr = ft_strjoin(tmp, "/");
		free(tmp);
		ptr++;
	}
	return (path);
}

static int	bin_command(char **av, t_list *lstenv)
{
	char	**env;
	char	**path;
	char	*tmp;

	if (fork() == 0)
	{
		env = list_2dar(lstenv);
		if (av[0][0] == '/' && execve(av[0], av, env) == -1
			&& !access(tmp, F_OK) && access(tmp, X_OK))
			permission_denied("my_shell", av[0], 1);
		if ((path = get_path(lstenv)))
			while (*path)
			{
				tmp = ft_strjoin(*path++, av[0]);
				if (execve(tmp, av, env) == -1 && !access(tmp, F_OK) &&
					access(tmp, X_OK))
					permission_denied("my_shell", tmp, 1);
				free(tmp);
			}
		return (0);
	}
	wait(0);
	return (1);
}

void	parse_command(char **av, t_list **lstenv)
{
	int		ac;

	ac = 0;
	while (av[ac])
		ac++;
	if (ft_strequ(av[0], "exit"))
		exit(0);
	if (ft_strequ(av[0], "echo"))
		ms_echo(ac, av);
	else if (ft_strequ(av[0], "env"))
		ms_print_env(*lstenv);
	else if (ft_strequ(av[0], "setenv"))
		ms_env_func(ac, av, lstenv);
	else if (ft_strequ(av[0], "unsetenv"))
		ms_env_func(ac, av, lstenv);
	else if (ft_strequ(av[0], "cd"))
		ms_change_dir(ac, av, lstenv);
	else if (!bin_command(av, *lstenv))
		command_not_found(av[0]);
}
