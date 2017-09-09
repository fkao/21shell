/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 15:07:16 by fkao              #+#    #+#             */
/*   Updated: 2017/09/08 15:20:57 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ms_countstr(char *in)
{
	int	i;

	i = 0;
	while (*in)
	{
		if (!ft_isspace(*in) && (ft_isspace(*(in + 1)) || *(in + 1) == '\0'))
			i++;
		in++;
	}
	return (i);
}

char	**split_whitespace(char *in)
{
	int		i;
	int		row;
	char	**av;

	av = (char**)ft_memalloc(sizeof(*av) * (ms_countstr(in) + 1));
	row = 0;
	while (*in)
	{
		i = 0;
		while (ft_isspace(*in))
			in++;
		while (!ft_isspace(in[i]) && in[i])
			i++;
		if (i)
			av[row++] = ft_strsub(in, 0, i);
		in += i;
	}
	av[row] = 0;
	return (av);
}
