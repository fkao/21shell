/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 12:00:08 by fkao              #+#    #+#             */
/*   Updated: 2017/11/20 10:46:47 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	parse_error(char **file)
{
	free(*file);
	write(2, RED "my_shell: parse error near '\\n'\n" RESET, 41);
	return (0);
}

static int	redirect_output(char *file)
{
	int	fd;

	if (file)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,
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
	char	*file;
	char	*front;
	char	*back;
	char	*tmp;
	int		len;

	len = 0;
	file = NULL;
	if ((front = ft_strchr(buf, '>')))
	{
		tmp = front++;
		while (ft_isspace(*front))
			front++;
		while (!ft_isspace(front[len]) && front[len])
			len++;
		file = ft_strsub(front, 0, len);
		back = ft_strdup(front + len);
		ft_bzero((void*)tmp, ft_strlen(tmp));
		ft_strcat(buf, back);
		free(back);
		if (!*file)
			return (parse_error(&file));
	}
	return (redirect_output(file));
}
