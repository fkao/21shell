/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 10:53:02 by fkao              #+#    #+#             */
/*   Updated: 2017/11/29 16:33:55 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	does_not_exist(int ac, char *str1, char *str2)
{
	ft_dprintf(2, RED "cd: no such file or directory: %s\n" RESET,
		(ac == 2) ? str1 : str2);
}

void	permission_denied(char *cmd, char *str, int close)
{
	ft_dprintf(2, RED "%s: permission denied: %s\n" RESET, cmd, str);
	if (close)
		exit(1);
}

void	command_not_found(char *str)
{
	ft_dprintf(2, RED "my_shell: command not found: %s\n" RESET, str);
	exit(1);
}

void	str_not_found(char *str)
{
	ft_dprintf(2, RED "cd: string not in pwd: %s\n", str);
}

void	error_message(char *str)
{
	ft_dprintf(2, RED "%s\n" RESET, str);
}
