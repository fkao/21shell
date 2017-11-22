/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:18:40 by fkao              #+#    #+#             */
/*   Updated: 2017/11/20 10:46:54 by fkao             ###   ########.fr       */
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

void	signal_handler(int signo)
{
	int		status;
	char	*buf;

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
}

void	signal_exit(int signo)
{
	if (signo == SIGINT)
		exit(2);
}
