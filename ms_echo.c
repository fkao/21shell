/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 11:01:49 by fkao              #+#    #+#             */
/*   Updated: 2017/11/20 10:46:33 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static void	fill_qoutes(t_echo *ret)
{
	char	*tmp;

	if (*ret->buf != '\'' && *ret->buf != '\"')
		*(ret->ptr++) = *(ret->buf++);
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
				*(ret->ptr++) = *(tmp++);
		}
		ret->buf++;
	}
}

static void	echo_env(t_echo *ret, t_list *lstenv)
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

static void	check_space(t_echo *ret)
{
	if ((*ret->buf == ' ' || *ret->buf == '\t') && !ret->quote)
	{
		*(ret->ptr++) = ' ';
		while (*ret->buf == ' ' || *ret->buf == '\t')
			ret->buf++;
	}
}

static void	check_quote(t_echo *ret, t_list *lstenv)
{
	while (*ret->buf)
	{
		check_space(ret);
		echo_env(ret, lstenv);
		fill_qoutes(ret);
		if (ret->quote && !*ret->buf)
		{
			(ret->quote == '\'') ? write(1, YEL "quote> " RESET, 17) :
			write(1, YEL "dquote> " RESET, 18);
			grab_commands(ret->buf);
			ft_strcat(ret->buf, "\n");
		}
	}
}

void		ms_echo(char *buf, t_list *lstenv)
{
	static t_echo	ret;

	if (fork() == 0)
	{
		signal(SIGINT, signal_exit);
		ft_bzero((void*)ret.str, BUF_SIZE);
		ft_bzero((void*)ret.new, BUF_SIZE);
		ret.quote = 0;
		ft_strcpy(ret.str, buf);
		ft_strcat(ret.str, "\n");
		ret.ptr = ret.new;
		ret.buf = ret.str;
		while (*ret.buf == ' ' || *ret.buf == '\t')
			ret.buf++;
		check_quote(&ret, lstenv);
		ft_putstr(ret.new);
		exit(0);
	}
	wait(0);
}
