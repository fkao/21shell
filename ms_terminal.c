/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_terminal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:03:50 by fkao              #+#    #+#             */
/*   Updated: 2017/10/31 12:13:58 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long	g_cur = 0;

void	move_cursor(int key, char *buf)
{
	if (key == LEFT && g_cur > 0)
	{
		MV_LEFT;
		g_cur--;
	}
	if (key == RIGHT && g_cur < (ft_strlen(buf)))
	{
		MV_RIGHT;
		g_cur++;
	}
}

void	edit_delete(char *buf)
{
	char	*cur_pos;
	char	*back;

	cur_pos = buf + g_cur;
	back = ft_strdup(cur_pos);
	g_cur--;
	*(buf + g_cur) = '\0';
	MV_LEFT;
	ft_putstr(tgetstr("dc", NULL));
	if (*back)
		ft_strcat(buf, back);
	free(back);
}

void	edit_insert(char *buf, char *key)
{
	char	*tmp;

	tmp = ft_strjoin(key, buf + g_cur);
	*(buf + g_cur) = '\0';
	ft_strcat(buf, tmp);
	ft_putstr(tgetstr("im", NULL));
	ft_putstr(key);
	ft_putstr(tgetstr("ei", NULL));
	g_cur++;
}

void	grab_commands(char *buf)
{
	char	*key;

	key = ft_strnew(5);
	while (read(0, key, 5))
	{
		if (ft_isprint(key[0]) && ft_strlen(key) == 1)
			edit_insert(buf, key);
		if (key[0] == ENTER)
		{
			ft_strcat(buf, "\n");
			write(1, "\n", 1);
			g_cur = 0;
			free(key);
			break ;
		}
		if (key[0] == DELETE && g_cur)
			edit_delete(buf);
		if (key[0] == 27)
			(key[2] == LEFT || key[2] == RIGHT) ? move_cursor(key[2], buf) : 0 ;
		ft_bzero((void*)key, 5);
	}
}
