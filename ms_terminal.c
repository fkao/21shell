/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_terminal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:03:50 by fkao              #+#    #+#             */
/*   Updated: 2017/11/22 12:58:04 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

t_hist			*g_hist;

void		store_command(char *buf)
{
	t_hist	*new;

	if (*buf)
	{
		new = (t_hist*)malloc(sizeof(*new));
		new->cmd = ft_strdup(buf);
		new->next = g_hist;
		new->prev = NULL;
		if (g_hist != NULL)
			g_hist->prev = new;
		g_hist = new;
	}
}

static void	put_history(char *buf, t_hist *hist, t_post *post)
{
	size_t	i;

	i = 0;
	if (*buf)
	{
		if (post->curs)
			ft_printf("\033[%dD", post->curs);
		tputs(tgetstr("ce", NULL), 1, int_putchar);
	}
	ft_bzero((void*)buf, BUF_SIZE);
	ft_strcpy(buf, hist->cmd);
	post->curs = ft_strlen(buf);
	ft_putstr(buf);
}

static void	term_history(int key, char *buf, t_hist **hist, t_post *post)
{
	if (key == UP && (*hist))
	{
		if ((*hist)->next && !post->hist)
			(*hist) = (*hist)->next;
		put_history(buf, *hist, post);
		post->hist = 0;
	}
	if (key == DOWN && (*hist))
	{
		if ((*hist)->prev)
			(*hist) = (*hist)->prev;
		put_history(buf, *hist, post);
	}
}

void		grab_commands(char *buf)
{
	char	*input;
	t_hist	*hist;
	t_post	post;

	hist = g_hist;
	post.curs = 0;
	post.hist = 1;
	input = ft_strnew(5);
	while (read(0, input, 5) && input[0] != ENTER)
	{
		if (ft_isprint(input[0]))
			edit_insert(buf, input, &post);
		if (input[0] == DELETE && post.curs)
			edit_delete(buf, &post);
		if (input[0] == 27)
		{
			move_cursor(input[2], buf, &post);
			(input[2] == UP || input[2] == DOWN) ?
				term_history(input[2], buf, &hist, &post) : 0;
		}
		ft_bzero((void*)input, 5);
	}
	write(1, "\n", 1);
	free(input);
}
