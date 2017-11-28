/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 10:35:10 by fkao              #+#    #+#             */
/*   Updated: 2017/11/27 17:12:16 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"
#include <pwd.h>
#include <sys/stat.h>

char	**get_path(t_list *lstenv)
{
	char	**path;
	char	**ptr;
	char	*tmp;

	if (!(tmp = get_envar(lstenv, "PATH=")))
		return (NULL);
	path = ft_strsplit(tmp, ':');
	ptr = path;
	while (*ptr)
	{
		tmp = *ptr;
		*ptr = ft_strjoin(tmp, "/");
		free(tmp);
		ptr++;
	}
	return (path);
}

char	**list_2dar(t_list *lstenv)
{
	int		count;
	char	**env;
	t_list	*tmp;

	count = 0;
	tmp = lstenv;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	env = (char**)ft_memalloc(sizeof(char*) * (count + 1));
	count = 0;
	while (lstenv)
	{
		env[count] = ft_strdup((char*)lstenv->content);
		count++;
		lstenv = lstenv->next;
	}
	return (env);
}

t_list	*init_env(void)
{
	extern char	**environ;
	t_list		*lstenv;

	lstenv = NULL;
	while (*environ)
	{
		ft_lstadd(&lstenv, ft_lstnew(*environ, ft_strlen(*environ) + 1));
		environ++;
	}
	ft_lstrev(&lstenv);
	return (lstenv);
}

void	ms_put_prompt(void)
{
	char	cwd[PATH_MAX];

	write(1, GRN BOLD, 10);
	getcwd(cwd, PATH_MAX);
	write(1, cwd, ft_strlen(cwd));
	write(1, "> " RESET, 7);
}

void	ms_init_shell(void)
{
	t_wins			win;
	unsigned short	i;
	int				pad;

	CM_MODE;
	MV_HOME;
	win = get_win_size(1);
	pad = 44 + (win.ws_col - 44) / 2;
	write(1, CYN "\n", 6);
	ft_printf("%*s", pad, "       ::::::::      :::                ::: \n");
	ft_printf("%*s", pad, "     :+:    :+:   :+:+:                :+:  \n");
	ft_printf("%*s", pad, "          +:+      +:+       +:+:+    +:+   \n");
	ft_printf("%*s", pad, "       +#+        +#+     +#+        +:+:+:+\n");
	ft_printf("%*s", pad, "    +#+          +#+       +#+#+    +#+  +#+\n");
	ft_printf("%*s", pad, "  #+#           #+#           #+#  #+#  #+# \n");
	ft_printf("%*s", pad, "#########   #########   ######    ###  ###  \n");
	i = -1;
	while (++i < win.ws_col)
		ft_putchar('*');
	write(1, "\n" RESET, 6);
}
