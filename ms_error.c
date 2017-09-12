/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 10:53:02 by fkao              #+#    #+#             */
/*   Updated: 2017/09/11 11:10:07 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	permission_denied(char *str)
{
	write(2, RED "minishell: permission denied: ", 35);
	write(2, str, ft_strlen(str));
	write(2, "\n" RESET, 6);
	exit(1);
}

void	command_not_found(char *str)
{
	write(2, RED "minishell: command not found: ", 35);
	write(2, str, ft_strlen(str));
	write(2, "\n" RESET, 6);
	exit(1);
}
