/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 15:16:27 by fkao              #+#    #+#             */
/*   Updated: 2017/09/08 16:45:31 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_stack(int ac, char **av)
{
	int	i;

	i = -1;
	while (++i < ac)
	{
		free(av[i]);
	}
	free(av);
}

int		bin_command(char **av, t_list *lstenv)
{
	pid_t	pid;
	char	**env;
	char	**path;
	char	*tmp;

	pid = fork();
	if (pid == 0)
	{
		env = list_2dar(lstenv);
		(av[0][0] == '/') ? execve(av[0], av, env) : 0;
		if ((path = get_path(lstenv)))
			while (*path)
			{
				tmp = ft_strjoin(*path, av[0]);
				if (execve(tmp, av, env) == -1)
				{
					free(tmp);
					path++;
				}
			}
		return (0);
	}
	wait(&pid);
	return (1);
}

void	parse_command(char *buf, t_list **lstenv)
{
	int		ac;
	char	**av;

	buf[ft_strlen(buf) - 1] = '\0';
	ac = ms_countstr(buf);
	av = split_whitespace(buf);
	if (ft_strequ(av[0], "echo"))
		check_quote(buf + 5, *lstenv);
	else if (ft_strequ(av[0], "env"))
		ms_print_env(*lstenv);
	else if (ft_strequ(av[0], "setenv"))
		ms_env_func(ac, av, lstenv);
	else if (ft_strequ(av[0], "unsetenv"))
		ms_env_func(ac, av, lstenv);
	else if (ft_strequ(av[0], "cd"))
		ms_change_dir(ac, av, lstenv);
	else if (!bin_command(av, *lstenv))
	{
		write(2, RED, 5);
		write(2, av[0], ft_strlen(av[0]));
		write(2, ": command not found\n" RESET, 25);
		exit(1);
	}
	free_stack(ac, av);
}

void	minishell(t_list *lstenv)
{
	char	*buf;
	char	cwd[PATH_MAX];

	buf = malloc(sizeof(char) * BUF_SIZE);
	while (1)
	{
		getcwd(cwd, PATH_MAX);
		write(1, GRN, 5);
		write(1, cwd, ft_strlen(cwd));
		write(1, "> " RESET, 7);
		ft_bzero((void*)buf, BUF_SIZE);
		read(0, buf, BUF_SIZE);
		if (ft_strequ(buf, "exit\n"))
			break ;
		else
			parse_command(buf, &lstenv);
	}
	free(buf);
}

int		main(int ac, char **av, char **extenv)
{
	t_list	*lstenv;

	(void)ac;
	(void)av;
	lstenv = init_env(extenv);
	minishell(lstenv);
	return (0);
}
