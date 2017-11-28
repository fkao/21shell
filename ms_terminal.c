/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_terminal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:03:50 by fkao              #+#    #+#             */
/*   Updated: 2017/11/27 18:08:00 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

t_hist		*store_command(char *buf)
{
	static t_hist	*hist = NULL;
	t_hist			*new;

	if (buf && *buf)
	{
		new = (t_hist*)malloc(sizeof(*new));
		new->cmd = ft_strdup(buf);
		new->next = hist;
		new->prev = NULL;
		if (hist != NULL)
			hist->prev = new;
		hist = new;
	}
	return (hist);
}

static void	clear_cmd_line(unsigned long *curs, char *buf)
{
	if (*curs)
		ft_printf("\033[%dD", *curs);
	CL_ENDL;
	ft_bzero((void*)buf, BUF_SIZE);
	*curs = 0;
}

static void	put_history(char *buf, t_hist *hist, t_post *post)
{
	clear_cmd_line(&post->curs, buf);
	ft_strcpy(buf, hist->cmd);
	post->curs = ft_strlen(buf);
	ft_putstr(buf);
}

static void	term_history(int key, char *buf, t_hist **hist, t_post *post)
{
	if (key == K_UP && (*hist))
	{
		if ((*hist)->next && !post->hist)
			(*hist) = (*hist)->next;
		put_history(buf, *hist, post);
		post->hist = 0;
	}
	if (key == K_DOWN && (*hist))
	{
		if ((*hist)->prev)
		{
			(*hist) = (*hist)->prev;
			put_history(buf, *hist, post);
		}
	}
}

void		grab_commands(char *buf)
{
	char	*input;
	t_hist	*hist;
	t_post	post;

	hist = store_command(NULL);
	post.curs = 0;
	post.hist = 1;
	input = ft_strnew(5);
	while (read(0, input, 5) && input[0] != K_ENTER)
	{
		if (ft_isprint(input[0]))
			edit_insert(buf, input, &post);
		if (input[0] == K_DELETE && post.curs)
			edit_delete(buf, &post);
		if (ft_strnequ(input, "\x1B\x5B", 2))
		{
			move_cursor(input[2], buf, &post);
			term_history(input[2], buf, &hist, &post);
		}
		if (input[0] == K_CTRL_U)
			clear_cmd_line(&post.curs, buf);
		ft_bzero((void*)input, 5);
	}
	write(1, "\n", 1);
	free(input);
}
