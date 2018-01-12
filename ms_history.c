/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 12:29:38 by fkao              #+#    #+#             */
/*   Updated: 2017/12/15 10:20:50 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

t_hist		*store_command(char *buf)
{
	static t_hist	*hist = NULL;
	t_hist			*new;

	if (buf && *buf)
	{
		new = (t_hist*)malloc(sizeof(*new));
		new->cmd = ft_strdup(buf);
		new->next = hist;
		new->prev = NULL;
		if (hist != NULL)
			hist->prev = new;
		hist = new;
	}
	return (hist);
}

static void	put_history(char *buf, t_hist *hist, t_help *cmdl)
{
	cmdl->buf_len = ft_strlen(buf);
	clear_cmd_line(buf, cmdl);
	ft_strcpy(buf, hist->cmd);
	cmdl->buf_len = ft_strlen(buf);
	cmdl->curs_pos = cmdl->buf_len;
	ft_putstr(buf);
}

static void	term_history(int key, char *buf, t_hist **hist, t_help *cmdl)
{
	if (key == K_UP && (*hist))
	{
		if ((*hist)->next && !cmdl->lst_front)
			(*hist) = (*hist)->next;
		put_history(buf, *hist, cmdl);
		cmdl->lst_front = 0;
	}
	if (key == K_DOWN && (*hist))
	{
		if ((*hist)->prev)
		{
			(*hist) = (*hist)->prev;
			put_history(buf, *hist, cmdl);
		}
	}
}

void		parse_arrows(char *buf, char *input, t_hist **hist, t_help *cmdl)
{
	if (ft_strnequ(input, "\x1B\x5B", 2))
	{
		term_history(input[2], buf, hist, cmdl);
		move_cursor(input[2], cmdl);
	}
	if (ft_strnequ(input, "\x1B\x1B\x5B", 3))
	{
		move_alt_left(input[3], buf, cmdl);
		move_alt_right(input[3], buf, cmdl);
	}
}
