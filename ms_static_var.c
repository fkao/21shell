/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_static_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 12:22:48 by fkao              #+#    #+#             */
/*   Updated: 2017/12/07 12:16:31 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		*check_interrupt(int i)
{
	static int	loop = 0;

	if (i == 1)
		loop = 1;
	if (i == 2)
		loop = 0;
	return (&loop);
}

char	*get_cmd_buf(void)
{
	static char	*buf;

	if (!buf)
		buf = (char*)malloc(sizeof(char) * BUF_SIZE);
	ft_bzero((void*)buf, BUF_SIZE);
	return (buf);
}

t_help	*get_cur_help(int i)
{
	static t_help	cmdl;

	if (i == 0)
	{
		cmdl.buf_len = 0;
		cmdl.curs_pos = 0;
		cmdl.lst_front = 1;
	}
	return (&cmdl);
}

t_wins	get_win_size(void)
{
	t_wins	win;
	t_help	*cmdl;

	ioctl(0, TIOCGWINSZ, &win);
	cmdl = get_cur_help(1);
	cmdl->win_col = win.ws_col;
	return (win);
}
