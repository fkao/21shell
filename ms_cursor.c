/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cursor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 11:18:49 by fkao              #+#    #+#             */
/*   Updated: 2017/12/04 14:23:30 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static void	move_cur_right(t_help *cmdl)
{
	cmdl->curs_col = (cmdl->curs_pos + cmdl->prompt_len) % cmdl->win_col;
	if (cmdl->curs_col == 0)
	{
		MC_DOWN;
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, int_putchar);
	}
	else
		MC_RIGHT;
}

void		move_cur_end(t_help *cmdl)
{
	int i;

	cmdl->curs_row = (cmdl->curs_pos + cmdl->prompt_len) / cmdl->win_col;
	cmdl->endl_col = (cmdl->buf_len + cmdl->prompt_len) % cmdl->win_col;
	cmdl->endl_row = (cmdl->buf_len + cmdl->prompt_len) / cmdl->win_col;
	i = -1;
	if (++i < cmdl->endl_row - cmdl->curs_row)
		MC_DOWN;
	tputs(tgoto(tgetstr("ch", NULL), 0, cmdl->endl_col - 1), 1, int_putchar);
}

void		move_cursor(int key, t_help *cmdl)
{
	if (key == K_LEFT && cmdl->curs_pos > 0)
	{
		MC_LEFT;
		cmdl->curs_pos--;
	}
	if (key == K_RIGHT && cmdl->curs_pos < cmdl->buf_len)
	{
		move_cur_right(cmdl);
		cmdl->curs_pos++;
	}
	if (key == K_HOME && cmdl->curs_pos > 0)
	{
		ft_printf("\033[%dD", cmdl->curs_pos);
		cmdl->curs_pos = 0;
	}
	if (key == K_END && (cmdl->curs_pos < cmdl->buf_len))
	{
		move_cur_end(cmdl);
		cmdl->curs_pos = cmdl->buf_len;
	}
}

void		move_alt_left(int key, char *buf, t_help *cmdl)
{
	if (key == K_LEFT && cmdl->curs_pos > 0)
	{
		MC_LEFT;
		cmdl->curs_pos--;
		while (buf[cmdl->curs_pos] == ' ' && cmdl->curs_pos > 0)
		{
			MC_LEFT;
			cmdl->curs_pos--;
		}
		while (ft_isprint(buf[cmdl->curs_pos]) && buf[cmdl->curs_pos - 1] != ' '
			&& cmdl->curs_pos > 0)
		{
			MC_LEFT;
			cmdl->curs_pos--;
		}
	}
}

void		move_alt_right(int key, char *buf, t_help *cmdl)
{
	if (key == K_RIGHT && cmdl->curs_pos < cmdl->buf_len)
	{
		move_cur_right(cmdl);
		cmdl->curs_pos++;
		while (buf[cmdl->curs_pos] == ' ' && cmdl->curs_pos < cmdl->buf_len)
		{
			move_cur_right(cmdl);
			cmdl->curs_pos++;
		}
		while (ft_isprint(buf[cmdl->curs_pos]) && buf[cmdl->curs_pos] != ' '
			&& cmdl->curs_pos < cmdl->buf_len)
		{
			move_cur_right(cmdl);
			cmdl->curs_pos++;
		}
	}
}
