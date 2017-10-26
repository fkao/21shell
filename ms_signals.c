/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:18:40 by fkao              #+#    #+#             */
/*   Updated: 2017/10/25 17:18:55 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signo)
{
	int	status;

	status = 0;
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		waitpid(-1, &status, 0);
		if (!WIFSIGNALED(status))
			ms_put_prompt();
	}
}
