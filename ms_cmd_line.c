/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:58:11 by fkao              #+#    #+#             */
/*   Updated: 2017/12/15 13:52:34 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static void	clear_cur_back(t_help *cmdl)
{
	int i;

	tputs(tgetstr("ce", NULL), 1, int_putchar);
	cmdl->curs_row = (cmdl->curs_pos + cmdl->prompt_len) / cmdl->win_col;
	cmdl->endl_row = (cmdl->buf_len + cmdl->prompt_len) / cmdl->win_col;
	i = cmdl->curs_row;
	if (i < cmdl->endl_row)
	{
		SV_CURS;
		while (i < cmdl->endl_row)
		{
			MC_DOWN;
			tputs(tgetstr("cb", NULL), 1, int_putchar);
			tputs(tgetstr("ce", NULL), 1, int_putchar);
			i++;
		}
		RE_CURS;
	}
}

void		clear_cmd_line(char *buf, t_help *cmdl)
{
	if (cmdl->curs_pos)
		ft_printf("\033[%dD", cmdl->curs_pos);
	cmdl->curs_pos = 0;
	clear_cur_back(cmdl);
	ft_bzero((void*)buf, BUF_SIZE);
	cmdl->buf_len = 0;
}

static void	edit_delete(char *buf, t_help *cmdl)
{
	char	back[BUF_SIZE];
	char	*tmp;

	ft_bzero((void*)back, cmdl->buf_len);
	ft_strcpy(back, buf + cmdl->curs_pos);
	cmdl->curs_pos--;
	tmp = buf + cmdl->curs_pos;
	ft_bzero((void*)tmp, ft_strlen(tmp));
	if (*back)
		ft_strcat(buf, back);
	MC_LEFT;
	clear_cur_back(cmdl);
	ft_putstr(tmp);
	if ((cmdl->buf_len - cmdl->curs_pos) > 1)
		ft_printf("\033[%dD", cmdl->buf_len - cmdl->curs_pos - 1);
	cmdl->buf_len--;
}

static void	edit_insert(char *buf, char *input, t_help *cmdl)
{
	char	tmp[BUF_SIZE];
	int		new_len;
	int		in_len;

	in_len = ft_strlen(input);
	if ((new_len = cmdl->buf_len + in_len) >= 4096)
	{
		move_cur_end(cmdl);
		error_message("my_shell: command overflow");
		return ;
	}
	ft_bzero((void*)tmp, new_len + 1);
	ft_strncpy(tmp, buf, cmdl->curs_pos);
	ft_strcat(tmp, input);
	ft_strcat(tmp, buf + cmdl->curs_pos);
	ft_strcpy(buf, tmp);
	cmdl->buf_len = new_len;
	ft_putstr(buf + cmdl->curs_pos);
	if ((cmdl->buf_len - cmdl->curs_pos) > 1)
		ft_printf("\033[%dD", cmdl->buf_len - cmdl->curs_pos - 1);
	cmdl->curs_pos += ft_strlen(input);
}

void		grab_commands(char *buf)
{
	char	*input;
	t_hist	*hist;
	t_help	*cmdl;

	raw_terminal_mode();
	hist = store_command(NULL);
	cmdl = get_cur_help(0);
	input = ft_strnew(6);
	while (read(0, input, 6) && input[0] != K_ENTER)
	{
		if (ft_isprint(input[0]))
			edit_insert(buf, input, cmdl);
		if (input[0] == K_DELETE && cmdl->curs_pos)
			edit_delete(buf, cmdl);
		if (input[0] == K_CTRL_U)
			clear_cmd_line(buf, cmdl);
		if (input[0] == K_CTRL_D)
			exit(0);
		if (input[0] == K_ESC)
			parse_arrows(buf, input, &hist, cmdl);
		ft_bzero((void*)input, 5);
	}
	move_cur_end(cmdl);
	write(1, "\n", 1);
	free(input);
}
