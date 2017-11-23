/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 12:00:08 by fkao              #+#    #+#             */
/*   Updated: 2017/11/22 17:15:00 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	parse_error(char **file)
{
	free(*file);
	write(2, RED "my_shell: parse error near '\\n'\n" RESET, 41);
	return (0);
}

static int	redirect_output(char *file, int append)
{
	int	fd;

	if (file)
	{
		fd = open(file, O_WRONLY | O_CREAT | ((append) ? O_APPEND : O_TRUNC),
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		free(file);
		if (fd == -1)
		{
			permission_denied("my_shell", file, 0);
			return (0);
		}
		dup2(fd, 1);
	}
	return (1);
}

int	parse_redirect(char *buf)
{
	t_rdir	rdir;

	rdir.len = 0;
	rdir.append = 0;
	rdir.file = NULL;
	if ((rdir.front = ft_strchr(buf, '>')))
	{
		rdir.tmp = rdir.front++;
		if (*(rdir.front++) == '>')
			rdir.append = 1;
		while (ft_isspace(*(rdir.front)))
			rdir.front++;
		while (!ft_isspace(rdir.front[rdir.len]) && rdir.front[rdir.len])
			rdir.len++;
		rdir.file = ft_strsub(rdir.front, 0, rdir.len);
		rdir.back = ft_strdup(rdir.front + rdir.len);
		ft_bzero((void*)rdir.tmp, ft_strlen(rdir.tmp));
		ft_strcat(buf, rdir.back);
		free(rdir.back);
		if (!*(rdir.file))
			return (parse_error(&rdir.file));
	}
	return (redirect_output(rdir.file, rdir.append));
}
