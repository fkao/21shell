/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 12:00:08 by fkao              #+#    #+#             */
/*   Updated: 2018/01/12 12:45:05 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"
//
static int	redirect_error(char *file)
{
	if (!file)
		error_message("my_shell: parse error near '\\n'");
	else
		ft_dprintf(2, RED "my_shell: parse error near '%c'\n" RESET, *file);
	return (0);
}

static int	redirect_output(char *file, int append)
{
	int	fd;

	if (file)
	{
		fd = open(file, O_WRONLY | O_CREAT | ((append) ? O_APPEND : O_TRUNC),
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
		{
			permission_denied("my_shell", file, 0);
			return (0);
		}
		dup2(fd, 1);
	}
	return (1);
}

static void	remove_nodes(t_list **trail, t_list **current, int append)
{
	int	i;
	int	n;
	t_list	*tmp;
	t_list	*here;

	n = (append) ? 3 : 2;
	i = 0;
	here = (*trail)->next;
	while (i < n)
	{
		tmp = here;
		here = here->next;
		i++;
		ft_lstdelone(&tmp, del_node);
	}
	*current = *trail;
	(*trail)->next = here;
}

/*
**	the list->content_size here is a assigned value where special characters are
**	0, normal inputs are 1, and subsituted variables are 2.
*/

int			parse_redirect(t_list *current)
{
	int		append;
	t_list	*trail;

	while (current)
	{
		append = 0;
		if (ft_strequ((char*)current->content, ">"))
		{
			if ((current = current->next))
				if (ft_strequ((char*)current->content, ">"))
				{
					append = 1;
					current = current->next;
				}
			if (!(current))
				return (redirect_error(0));
			if (current->content_size == 0)
					return (redirect_error(current->content));
			if (!redirect_output((char*)current->content, append))
				return (0);
			remove_nodes(&trail, &current, append);
		}
		trail = current;
		current = current->next;
	}
	return (1);
}

void		reset_stdout(void)
{
	static int	stdout;

	if (!stdout)
		stdout = dup(1);
	dup2(stdout, 1);
}
