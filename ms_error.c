/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 10:53:02 by fkao              #+#    #+#             */
/*   Updated: 2017/10/31 12:32:05 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	does_not_exist(int ac, char *str1, char *str2)
{
	write(2, RED "cd: no such file or directory: ", 36);
	if (ac == 2)
		write(2, str1, ft_strlen(str1));
	else
		write(2, str2, ft_strlen(str2));
	write(2, "\n" RESET, 6);
}

void	permission_denied(char *str, int iscmd)
{
	if (iscmd)
		write(2, RED "minishell: permission denied: ", 35);
	else
		write(2, RED "cd: permission denied: ", 28);
	write(2, str, ft_strlen(str));
	write(2, "\n" RESET, 6);
	if (iscmd)
		exit(1);
}

void	command_not_found(char *str)
{
	write(2, RED "minishell: command not found: ", 35);
	write(2, str, ft_strlen(str));
	write(2, "\n" RESET, 6);
	exit(1);
}
