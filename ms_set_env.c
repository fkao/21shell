/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 16:24:00 by fkao              #+#    #+#             */
/*   Updated: 2017/09/08 10:03:24 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_node(void *content, size_t content_size)
{
	free(content);
	(void)content_size;
}

void	unset_env(char *name, t_list **lstenv)
{
	t_list	*here;
	t_list	*trail;
	char	*fname;

	fname = ft_strjoin(name, "=");
	here = *lstenv;
	while (here)
	{
		if (ft_strnequ((char*)here->content, fname, ft_strlen(fname)))
		{
			if (here == *lstenv)
				*lstenv = (*lstenv)->next;
			else
				trail->next = here->next;
			ft_lstdelone(&here, del_node);
			break ;
		}
		trail = here;
		here = here->next;
	}
	free(fname);
}

void	set_env(char *name, char *var, t_list **lstenv)
{
	char	*fname;
	char	*newvar;
	t_list	*tmp;

	fname = ft_strjoin(name, "=");
	newvar = ft_strjoin(fname, var);
	if (!(tmp = *lstenv))
		ft_lstadd(lstenv, ft_lstnew(newvar, ft_strlen(newvar) + 1));
	else
	{
		while (tmp)
		{
			if (ft_strnequ((char*)tmp->content, fname, ft_strlen(fname)))
			{
				free((char*)tmp->content);
				tmp->content = ft_strdup(newvar);
				break ;
			}
			tmp = tmp->next;
		}
		if (tmp == NULL)
			ft_lstend(lstenv, ft_lstnew(newvar, ft_strlen(newvar) + 1));
	}
	free(newvar);
	free(fname);
}

void	ms_env_func(int ac, char **av, t_list **lstenv)
{
	if (ft_strequ(av[0], "setenv"))
	{
		if (ac != 3)
		{
			write(2, RED "usage: setenv [ENV_VAR] [value1:value2:...]\n" RESET,
			54);
			return ;
		}
		else
			set_env(av[1], av[2], lstenv);
	}
	else if (ft_strequ(av[0], "unsetenv"))
	{
		if (ac != 2)
		{
			write(2, RED "usage: unsetenv [ENV_VAR]\n" RESET, 36);
			return ;
		}
		else
			unset_env(av[1], lstenv);
	}
}

void	ms_print_env(t_list *lstenv)
{
	while (lstenv)
	{
		ft_printf("%s\n", (char*)lstenv->content);
		lstenv = lstenv->next;
	}
}
