/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 11:01:49 by fkao              #+#    #+#             */
/*   Updated: 2017/09/06 17:38:23 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_qoutes(t_echo *ret)
{
	char	*tmp;

	if (*ret->buf != '\'' && *ret->buf != '\"')
		*(ret->ptr)++ = *(ret->buf++);
	if (*ret->buf == '\'' || *ret->buf == '\"')
	{
		if (*ret->buf == ret->quote)
			ret->quote = 0;
		else
		{
			if (!ret->quote)
				ret->quote = *(ret->buf++);
			tmp = ret->buf;
			while (*ret->buf != ret->quote && *ret->buf)
				ret->buf++;
			if (*ret->buf == ret->quote)
				ret->quote = 0;
			while (*tmp != *ret->buf)
				*(ret->ptr++) = *tmp++;
		}
		ret->buf++;
	}
}

void	check_space(t_echo *ret)
{
	if (*ret->buf == ' ' && !ret->quote)
	{
		*(ret->ptr)++ = ' ';
		while (*ret->buf == ' ')
			ret->buf++;
	}
}

void	check_quote(char *buf)
{
	t_echo	*ret;

	buf[ft_strlen(buf)] = '\n';
	ret = (t_echo*)ft_memalloc(sizeof(t_echo));
	ret->buf = buf;
	ret->new = ft_strnew(BUF_SIZE);
	ret->ptr = ret->new;
	while (*ret->buf == ' ')
		ret->buf++;
	while (*ret->buf)
	{
		check_space(ret);
		fill_qoutes(ret);
		if (ret->quote && !*ret->buf)
		{
			(ret->quote == '\'') ? write(1, YEL "quote> " RESET, 17) :
			write(1, YEL "dquote> " RESET, 18);
			read(0, ret->buf, BUF_SIZE);
		}
	}
	ft_printf("%s", ret->new);
	free(ret->new);
	free(ret);
}
