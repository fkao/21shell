/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 10:35:10 by fkao              #+#    #+#             */
/*   Updated: 2017/12/15 16:10:31 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

char	**list_2dar(t_list *lst)
{
	int		count;
	char	**new;
	t_list	*tmp;

	count = 0;
	tmp = lst;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	new = (char**)ft_memalloc(sizeof(char*) * (count + 1));
	count = 0;
	while (lst)
	{
		new[count] = ft_strdup((char*)lst->content);
		count++;
		lst = lst->next;
	}
	return (new);
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
	t_help	*cmdl;

	getcwd(cwd, PATH_MAX);
	cmdl = get_cur_help(1);
	cmdl->prompt_len = ft_strlen(cwd) + 3;
	ft_printf(BOLD);
	ft_printf(GRN "%s> " RESET, cwd);
}

// void	ms_init_shell(void)
// {
// 	t_wins			win;
// 	unsigned short	i;
// 	int				pad;
//
// 	CM_MODE;
// 	MV_HOME;
// 	win = get_win_size();
// 	pad = 44 + (win.ws_col - 44) / 2;
// 	write(1, CYN "\n", 6);
// 	ft_printf("%*s", pad, "       ::::::::      :::                ::: \n");
// 	ft_printf("%*s", pad, "     :+:    :+:   :+:+:                :+:  \n");
// 	ft_printf("%*s", pad, "          +:+      +:+       +:+:+    +:+   \n");
// 	ft_printf("%*s", pad, "       +#+        +#+     +#+        +:+:+:+\n");
// 	ft_printf("%*s", pad, "    +#+          +#+       +#+#+    +#+  +#+\n");
// 	ft_printf("%*s", pad, "  #+#           #+#           #+#  #+#  #+# \n");
// 	ft_printf("%*s", pad, "#########   #########   ######    ###  ###  \n");
// 	i = -1;
// 	while (++i < win.ws_col)
// 		ft_putchar('*');
// 	write(1, RESET "\n", 6);
// }
