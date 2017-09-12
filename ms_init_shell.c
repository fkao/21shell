/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 10:35:10 by fkao              #+#    #+#             */
/*   Updated: 2017/09/11 11:37:35 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(t_list *lstenv)
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

char	**list_2dar(t_list *lstenv)
{
	int		count;
	char	**env;
	t_list	*tmp;

	count = 0;
	tmp = lstenv;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	env = (char**)ft_memalloc(sizeof(char*) * (count + 1));
	count = 0;
	while (lstenv)
	{
		env[count] = ft_strdup((char*)lstenv->content);
		count++;
		lstenv = lstenv->next;
	}
	return (env);
}

t_list	*init_env(char **extenv)
{
	t_list	*lstenv;

	lstenv = NULL;
	while (*extenv)
	{
		ft_lstadd(&lstenv, ft_lstnew(*extenv, ft_strlen(*extenv) + 1));
		extenv++;
	}
	ft_lstrev(&lstenv);
	return (lstenv);
}

void	ms_put_prompt(void)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	write(1, GRN, 5);
	write(1, cwd, ft_strlen(cwd));
	write(1, "> " RESET, 7);
}
