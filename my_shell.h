/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 17:44:42 by fkao              #+#    #+#             */
/*   Updated: 2017/11/22 17:13:07 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SHELL_H
# define MY_SHELL_H
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
# include <fcntl.h>


# define RED		"\x1B[31m"
# define GRN		"\x1B[32m"
# define YEL		"\x1B[33m"
# define RESET		"\x1B[0m"

# define BUF_SIZE	4096
# define ENTER		10
# define DELETE		127
# define UP			65
# define DOWN		66
# define RIGHT		67
# define LEFT		68
# define HOME		72
# define END		70

# define MV_RIGHT	tputs(tgetstr("nd", NULL), 1, int_putchar)
# define MV_LEFT	tputs(tgetstr("le", NULL), 1, int_putchar)
# define CL_ENDL	tputs(tgetstr("ce", NULL), 1, int_putchar)
# define DEL_CHAR	tputs(tgetstr("dc", NULL), 1, int_putchar)
# define INS_MODE	tputs(tgetstr("im", NULL), 1, int_putchar)
# define END_INS	tputs(tgetstr("ei", NULL), 1, int_putchar)

typedef struct		s_echo
{
	char			str[BUF_SIZE];
	char			*buf;
	char			*ptr;
	char			new[BUF_SIZE];
	char			quote;
}					t_echo;

typedef struct		s_hist
{
	char			*cmd;
	struct s_hist	*prev;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_post
{
	unsigned long	curs;
	int				hist;
}					t_post;

typedef struct		s_rdir
{
	char			*file;
	char			*front;
	char			*back;
	char			*tmp;
	int				len;
	int				append;
}					t_rdir;

/*
**	terminal
*/
void				ms_put_prompt(void);
void				signal_handler(int signo);
void				signal_exit(int signo);
char				*get_cmd_buf(void);
void				grab_commands(char *buf);
void				store_command(char *buf);
void				move_cursor(int key, char *buf, t_post *post);
void				edit_delete(char *buf, t_post *post);
void				edit_insert(char *buf, char *input, t_post *post);
int					parse_redirect(char *buf);

/*
**	builtins
*/
t_list				*init_env(void);
char				**list_2dar(t_list *lstenv);
char				**get_path(t_list *lstenv);
void				ms_echo(char *buf, t_list *lstenv);
void				ms_print_env(t_list *lstenv);
void				ms_env_func(int ac, char **av, t_list **lstenv);
void				ms_change_dir(int ac, char **av, t_list **lstenv);
void				set_env(char *name, char *var, t_list **lstenv);
char				*get_envar(t_list *lst, char *str);

/*
**	error message
*/
void				command_not_found(char *str);
void				permission_denied(char *cmd, char *str, int close);
void				does_not_exist(int ac, char *str1, char *str2);
#endif
