/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 12:24:32 by fkao              #+#    #+#             */
/*   Updated: 2017/12/19 16:03:38 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static void	add_to_list(t_inpt *in, char *arg, int i)
{
	t_list	*node;

	if (arg && *arg)
	{
		node = (t_list*)ft_memalloc(sizeof(*node));
		node->content = (void*)ft_strdup(arg);
		node->content_size = i;
		if (!in->head)
		{
			in->head = node;
			in->here = in->head;
		}
		else
		{
			in->here->next = node;
			in->here = in->here->next;
		}
	}
	ft_bzero((void*)in->new, BUF_SIZE);
	in->ptr = in->new;
}

static void	fill_qoutes(t_inpt *in)
{
	if (*in->buf != '\'' && *in->buf != '\"')
		*(in->ptr++) = *(in->buf++);
	if (*in->buf == '\'' || *in->buf == '\"')
	{
		if (*in->buf == in->quote)
		{
			in->quote = '\0';
			in->buf++;
		}
		else
		{
			if (!in->quote)
				in->quote = *(in->buf++);
			while (*in->buf != in->quote && *in->buf)
				*(in->ptr++) = *(in->buf++);
		}
	}
}

static void	cmd_subsitute(t_inpt *in, t_list *lstenv)
{
	if (!ft_isalnum(in->buf[1]))
		*(in->ptr++) = *(in->buf++);
	else
	{
		while (ft_isalnum(*(++in->buf)))
			*(in->ptr++) = *in->buf;
		*in->ptr = '=';
		add_to_list(in, get_envar(lstenv, in->new), 2);
	}
}

static void	traverse_input(t_inpt *in, t_list *lstenv)
{
	while (*in->buf)
	{
		while (*in->buf == ' ' && !in->quote)
			in->buf++;
		if (*in->buf == '$' && !in->quote)
			cmd_subsitute(in, lstenv);
		else if ((*in->buf == '>' || *in->buf == ';') && !in->quote)
		{
			add_to_list(in, in->new, 1);
			*(in->ptr++) = *(in->buf++);
			add_to_list(in, in->new, 0);
		}
		else
			fill_qoutes(in);
		if ((*in->buf == ' ' || !(*in->buf)) && !in->quote)
			add_to_list(in, in->new, 1);
		else if (!*in->buf && in->quote)
		{
			*(in->ptr++) = '\n';
			ft_printf(YEL "%s> " RESET,
				(in->quote == '\'') ? "quote" : "dquote");
			grab_commands(in->buf);
			if (*in->halt == 0)
				return ;
		}
	}
}

t_list		*argument_list(char *buf, t_list *lstenv)
{
	t_inpt	in;

	in.buf = buf;
	in.head = NULL;
	ft_bzero((void*)in.new, BUF_SIZE);
	in.ptr = in.new;
	in.quote = 0;
	in.halt = check_interrupt(1);
	traverse_input(&in, lstenv);
	check_interrupt(2);
	return (in.head);
}
