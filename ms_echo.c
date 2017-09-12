/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 11:01:49 by fkao              #+#    #+#             */
/*   Updated: 2017/09/11 11:54:13 by fkao             ###   ########.fr       */
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

void	echo_env(t_echo *ret, t_list *lstenv)
{
	char	*buf;
	char	*tmp;
	char	*env;

	if (*ret->buf == '$')
	{
		buf = ft_strdup(++ret->buf);
		tmp = buf;
		while (!ft_isspace(*ret->buf))
		{
			tmp++;
			ret->buf++;
		}
		*tmp = '\0';
		env = ft_strjoin(buf, "=");
		if ((tmp = get_envar(lstenv, env)))
			while (*tmp)
			{
				*(ret->ptr++) = *tmp++;
			}
		free(buf);
		free(env);
	}
}

void	check_space(t_echo *ret)
{
	if ((*ret->buf == ' ' || *ret->buf == '\t') && !ret->quote)
	{
		*(ret->ptr)++ = ' ';
		while (*ret->buf == ' ' || *ret->buf == '\t')
			ret->buf++;
	}
}

void	check_quote(char *buf, t_list *lstenv)
{
	t_echo	*ret;

	buf[ft_strlen(buf)] = '\n';
	ret = (t_echo*)ft_memalloc(sizeof(t_echo));
	ret->buf = buf;
	ret->new = ft_strnew(BUF_SIZE);
	ret->ptr = ret->new;
	while (*ret->buf == ' ' || *ret->buf == '\t')
		ret->buf++;
	while (*ret->buf)
	{
		check_space(ret);
		echo_env(ret, lstenv);
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
