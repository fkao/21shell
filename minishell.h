/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 17:44:42 by fkao              #+#    #+#             */
/*   Updated: 2017/09/11 12:03:44 by fkao             ###   ########.fr       */
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
# define BUF_SIZE 4096
# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define YEL	"\x1B[33m"
# define RESET	"\x1B[0m"

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
t_list			*init_env(char **extenv);
char			**list_2dar(t_list *lstenv);
char			**get_path(t_list *lstenv);
void			check_quote(char *buf, t_list *lstenv);
void			ms_print_env(t_list *lstenv);
void			ms_env_func(int ac, char **av, t_list **lstenv);
void			ms_change_dir(int ac, char **av, t_list **lstenv);
void			set_env(char *name, char *var, t_list **lstenv);
char			*get_envar(t_list *lst, char *str);
void			permission_denied(char *str);
void			command_not_found(char *str);
#endif
