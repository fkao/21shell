/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:18:40 by fkao              #+#    #+#             */
/*   Updated: 2017/12/12 14:13:46 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	signal_handler(int signo)
{
	int		status;

	status = 0;
	if (signo == SIGINT)
	{
		check_interrupt(2);
		write(1, "\n", 1);
		waitpid(-1, &status, 0);
		if (!WIFSIGNALED(status))
		{
			get_cmd_buf();
			get_cur_help(0);
			ms_put_prompt();
		}
	}
	if (signo == SIGWINCH)
		get_win_size();
}
