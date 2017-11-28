/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:18:40 by fkao              #+#    #+#             */
/*   Updated: 2017/11/27 15:46:27 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

char	*get_cmd_buf(void)
{
	static char	*buffer;

	if (!buffer)
		buffer = (char*)malloc(sizeof(char) * BUF_SIZE);
	ft_bzero((void*)buffer, BUF_SIZE);
	return (buffer);
}

t_wins	get_win_size(int i)
{
	static t_wins	win;

	if (i == 1)
		ioctl(0, TIOCGWINSZ, &win);
	return (win);
}

void	signal_handler(int signo)
{
	int				status;
	char			*buf;

	status = 0;
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		waitpid(-1, &status, 0);
		if (!WIFSIGNALED(status) && WEXITSTATUS(status) != 2)
		{
			buf = get_cmd_buf();
			ms_put_prompt();
		}
	}
	if (signo == SIGWINCH)
		get_win_size(1);
}

void	signal_exit(int signo)
{
	if (signo == SIGINT)
		exit(2);
}
