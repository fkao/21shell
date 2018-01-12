/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 17:44:42 by fkao              #+#    #+#             */
/*   Updated: 2017/12/15 16:00:20 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SHELL_H
# define MY_SHELL_H
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <limits.h>
# include <termios.h>
# include <term.h>
# include <fcntl.h>

# define RESET			"\x1B[0m"
# define BOLD			"\x1B[1m"
# define RED			"\x1B[31m"
# define GRN			"\x1B[32m"
# define YEL			"\x1B[33m"
# define BLU			"\x1B[34m"
# define MAG			"\x1B[35m"
# define CYN			"\x1B[36m"

# define BUF_SIZE		4096
# define K_ENTER		0x0A
# define K_ESC			0x1B
# define K_DELETE		0x7F
# define K_UP			0x41
# define K_DOWN			0x42
# define K_RIGHT		0x43
# define K_LEFT			0x44
# define K_HOME			0x48
# define K_END			0x46
# define K_CTRL_U		0x15
# define K_CTRL_D		0x04

# define MC_UP			tputs(tgetstr("up", NULL), 1, int_putchar)
# define MC_DOWN		tputs(tgetstr("do", NULL), 1, int_putchar)
# define MC_RIGHT		tputs(tgetstr("nd", NULL), 1, int_putchar)
# define MC_LEFT		tputs(tgetstr("le", NULL), 1, int_putchar)
# define CL_ENDL		tputs(tgetstr("ce", NULL), 1, int_putchar)
# define DEL_CHAR		tputs(tgetstr("dc", NULL), 1, int_putchar)
# define INS_MODE		tputs(tgetstr("im", NULL), 1, int_putchar)
# define END_INS		tputs(tgetstr("ei", NULL), 1, int_putchar)
# define CM_MODE		tputs(tgetstr("ti", NULL), 1, int_putchar)
# define CM_EXIT		tputs(tgetstr("te", NULL), 1, int_putchar)
# define MV_HOME		tputs(tgetstr("ho", NULL), 1, int_putchar)
# define SV_CURS		tputs(tgetstr("sc", NULL), 1, int_putchar)
# define RE_CURS		tputs(tgetstr("rc", NULL), 1, int_putchar)

typedef struct winsize	t_wins;
typedef struct			s_inpt
{
	char				*buf;
	char				new[BUF_SIZE];
	char				*ptr;
	char				quote;
	int					*halt;
	t_list				*head;
	t_list				*here;
}						t_inpt;

typedef struct			s_hist
{
	char				*cmd;
	struct s_hist		*prev;
	struct s_hist		*next;
}						t_hist;

typedef struct			s_help
{
	int					buf_len;
	int					curs_pos;
	int					prompt_len;
	int					lst_front;
	int					win_col;
	int					curs_col;
	int					curs_row;
	int					endl_col;
	int					endl_row;
}						t_help;

void					ms_init_shell(void);
void					reset_stdout(void);
void					ms_put_prompt(void);
void					grab_commands(char *buf);
t_hist					*store_command(char *buf);
int			parse_redirect(t_list *lstarg);
t_list		*argument_list(char *buf, t_list *lstenv);
void		parse_command(char **av, t_list **lstenv);
void		del_node(void *content, size_t content_size);

/*
**	terminal
*/
void					default_terminal_mode(void);
void					raw_terminal_mode(void);
void					parse_arrows(char *buf, char *input, t_hist **hist,
							t_help *cmdl);
void					move_cursor(int key, t_help *cmdl);
void					move_alt_left(int key, char *buf, t_help *cmdl);
void					move_alt_right(int key, char *buf, t_help *cmdl);
void					clear_cmd_line(char *buf, t_help *cmdl);
void					move_cur_end(t_help *cmdl);

/*
**	builtins
*/
t_list					*init_env(void);
char					**list_2dar(t_list *lstenv);
void		ms_echo(int ac, char **av);
void					ms_print_env(t_list *lstenv);
void					ms_env_func(int ac, char **av, t_list **lstenv);
void					ms_change_dir(int ac, char **av, t_list **lstenv);
void					set_env(char *name, char *var, t_list **lstenv);
char					*get_envar(t_list *lst, char *str);

/*
**	signals
*/
void					signal_handler(int signo);

/*
**	static variables
*/
int						*check_interrupt(int i);
char					*get_cmd_buf(void);
t_help					*get_cur_help(int i);
t_wins					get_win_size(void);

/*
**	error message
*/
void					error_message(char *str);
void					str_not_found(char *str);
void					command_not_found(char *str);
void					permission_denied(char *cmd, char *str, int close);
void					does_not_exist(int ac, char *str1, char *str2);
#endif
