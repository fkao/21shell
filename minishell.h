/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 17:44:42 by fkao              #+#    #+#             */
/*   Updated: 2017/10/31 12:32:04 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include <signal.h>
# include <termios.h>
# include <term.h>

# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define YEL	"\x1B[33m"
# define RESET	"\x1B[0m"

# define BUF_SIZE	4096
# define ENTER		10
# define DELETE		127
# define UP			65
# define DOWN		66
# define RIGHT		67
# define LEFT		68

# define MV_RIGHT	ft_putstr("\033[1C")
# define MV_LEFT	ft_putstr("\033[1D")

typedef struct	s_echo
{
	char		*buf;
	char		*ptr;
	char		*new;
	char		quote;
}				t_echo;

void			minishell(t_list *lstenv);
void			ms_put_prompt(void);
int				ms_countstr(char *input);
char			**split_whitespace(char *input);
t_list			*init_env(void);
char			**list_2dar(t_list *lstenv);
char			**get_path(t_list *lstenv);
void			check_quote(char *buf, t_list *lstenv);
void			ms_print_env(t_list *lstenv);
void			ms_env_func(int ac, char **av, t_list **lstenv);
void			ms_change_dir(int ac, char **av, t_list **lstenv);
void			set_env(char *name, char *var, t_list **lstenv);
char			*get_envar(t_list *lst, char *str);
void			command_not_found(char *str);
void			permission_denied(char *str, int iscmd);
void			does_not_exist(int ac, char *str1, char *str2);
void			signal_handler(int signo);
void			grab_commands(char *buf);
#endif
