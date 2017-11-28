/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 15:16:27 by fkao              #+#    #+#             */
/*   Updated: 2017/11/27 16:36:40 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static void	free_stack(int ac, char **av)
{
	int	i;

	i = -1;
	while (++i < ac)
		free(av[i]);
	free(av);
}

static int	bin_command(char **av, t_list *lstenv)
{
	char	**env;
	char	**path;
	char	*tmp;

	if (fork() == 0)
	{
		env = list_2dar(lstenv);
		if (av[0][0] == '/' && execve(av[0], av, env) == -1
			&& !access(tmp, F_OK) && access(tmp, X_OK))
			permission_denied("my_shell", av[0], 1);
		if ((path = get_path(lstenv)))
			while (*path)
			{
				tmp = ft_strjoin(*path, av[0]);
				if (execve(tmp, av, env) == -1 && !access(tmp, F_OK) &&
					access(tmp, X_OK))
					permission_denied("my_shell", tmp, 1);
				free(tmp);
				path++;
			}
		return (0);
	}
	wait(0);
	return (1);
}

static void	parse_command(char *buf, t_list **lstenv)
{
	int		ac;
	char	**av;

	if (!parse_redirect(buf))
		return ;
	ac = ft_countstr(buf, ' ');
	av = ft_strsplit(buf, ' ');
	if (ft_strequ(buf, "exit"))
	{
		CM_EXIT;
		exit(0);
	}
	else if (ft_strequ(av[0], "echo"))
		ms_echo(ft_strstr(buf, "echo") + 5, *lstenv);
	else if (ft_strequ(av[0], "env"))
		ms_print_env(*lstenv);
	else if (ft_strequ(av[0], "setenv"))
		ms_env_func(ac, av, lstenv);
	else if (ft_strequ(av[0], "unsetenv"))
		ms_env_func(ac, av, lstenv);
	else if (ft_strequ(av[0], "cd"))
		ms_change_dir(ac, av, lstenv);
	else if (!bin_command(av, *lstenv))
		command_not_found(av[0]);
	free_stack(ac, av);
}

static void	my_shell(t_list *lstenv)
{
	char	*buf;
	char	**av;
	char	**tmp;
	int		stdout;

	stdout = dup(1);
	while (1)
	{
		dup2(stdout, 1);
		ms_put_prompt();
		buf = get_cmd_buf();
		grab_commands(buf);
		store_command(buf);
		if (!*buf)
			continue ;
		else if (ft_strchr(buf, ';') && (av = ft_strsplit(buf, ';')))
		{
			tmp = av;
			while (*tmp)
				parse_command(*(tmp++), &lstenv);
			free_stack(ft_countstr(buf, ';'), av);
		}
		else
			parse_command(buf, &lstenv);
	}
	free(buf);
}

int			main(void)
{
	t_list			*lstenv;
	struct termios	term;

	if (tcgetattr(0, &term) == -1 || tgetent(NULL, getenv("TERM")) < 1)
		return (0);
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSANOW, &term);
	signal(SIGINT, signal_handler);
	signal(SIGWINCH, signal_handler);
	lstenv = init_env();
	ms_init_shell();
	my_shell(lstenv);
	return (0);
}
