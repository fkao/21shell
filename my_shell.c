/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 15:16:27 by fkao              #+#    #+#             */
/*   Updated: 2018/01/12 12:52:38 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static void	free_stack(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		free(av[i++]);
	free(av);
}

void	del_node(void *content, size_t content_size)
{
	free(content);
	(void)content_size;
}

// add piping

static void	my_shell(char *buf, t_list *lstenv)
{
	int		*quote;
	t_list	*lstarg;
	char	**av;

	quote = check_interrupt(0);
	if (*quote || !*buf)
		return ;
	else
	{
		store_command(buf);
		lstarg = argument_list(buf, lstenv);
		if (parse_redirect(lstarg))
		{
			av = list_2dar(lstarg);
			parse_command(av, &lstenv);
			free_stack(av);
		}
		ft_lstdel(&lstarg, del_node);
	}
}

int			main(void)
{
	t_list	*lstenv;
	char	*buf;

	tgetent(NULL, getenv("TERM"));
	signal(SIGINT, signal_handler);
	signal(SIGWINCH, signal_handler);
	lstenv = init_env();
	// ms_init_shell();
	get_win_size();
	while (42)
	{
		reset_stdout();
		ms_put_prompt();
		buf = get_cmd_buf();
		grab_commands(buf);
		default_terminal_mode();
		my_shell(buf, lstenv);
	}
	return (0);
}
