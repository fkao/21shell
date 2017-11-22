/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_edit_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:09:01 by fkao              #+#    #+#             */
/*   Updated: 2017/11/20 10:46:36 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	move_cursor(int key, char *buf, t_post *post)
{
	if (key == LEFT && post->curs > 0)
	{
		MV_LEFT;
		post->curs--;
	}
	if (key == RIGHT && post->curs < (ft_strlen(buf)))
	{
		MV_RIGHT;
		post->curs++;
	}
	if (key == HOME && post->curs > 0)
	{
		ft_printf("\033[%dD", post->curs);
		post->curs = 0;
	}
	if (key == END && (post->curs < ft_strlen(buf)))
	{
		ft_printf("\033[%dC", ft_strlen(buf) - post->curs);
		post->curs = ft_strlen(buf);
	}
}

void	edit_delete(char *buf, t_post *post)
{
	char	*curs;
	char	*back;

	curs = buf + post->curs;
	back = ft_strdup(curs);
	post->curs--;
	*(buf + post->curs) = '\0';
	MV_LEFT;
	tputs(tgetstr("dc", NULL), 1, int_putchar);
	if (*back)
		ft_strcat(buf, back);
	free(back);
}

void	edit_insert(char *buf, char *input, t_post *post)
{
	char	*tmp;

	tmp = ft_strjoin(input, buf + post->curs);
	*(buf + post->curs) = '\0';
	ft_strcat(buf, tmp);
	tputs(tgetstr("im", NULL), 1, int_putchar);
	ft_putstr(input);
	tputs(tgetstr("ei", NULL), 1, int_putchar);
	post->curs++;
	free(tmp);
}
