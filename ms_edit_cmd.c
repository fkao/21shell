/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_edit_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:09:01 by fkao              #+#    #+#             */
/*   Updated: 2017/11/27 11:56:23 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	move_cursor(int key, char *buf, t_post *post)
{
	if (key == K_LEFT && post->curs > 0)
	{
		MV_LEFT;
		post->curs--;
	}
	if (key == K_RIGHT && post->curs < (ft_strlen(buf)))
	{
		MV_RIGHT;
		post->curs++;
	}
	if (key == K_HOME && post->curs > 0)
	{
		ft_printf("\033[%dD", post->curs);
		post->curs = 0;
	}
	if (key == K_END && (post->curs < ft_strlen(buf)))
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
	DEL_CHAR;
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
	INS_MODE;
	ft_putstr(input);
	END_INS;
	post->curs++;
	free(tmp);
}
