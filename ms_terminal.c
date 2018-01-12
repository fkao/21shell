/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_terminal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:03:50 by fkao              #+#    #+#             */
/*   Updated: 2017/11/29 18:02:17 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	raw_terminal_mode(void)
{
	struct termios	tattr;

	tcgetattr(0, &tattr);
	tattr.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSANOW, &tattr);
}

void	default_terminal_mode(void)
{
	struct termios	tattr;

	tcgetattr(0, &tattr);
	tattr.c_lflag |= (ECHO | ICANON);
	tcsetattr(0, TCSANOW, &tattr);
}
