NAME	= minishell

INCL	= -I./libft/includes \
			-I ft_ls.h

SFILE	= minishell.c \
			ms_init_shell.c \
			ms_echo.c \
			ms_set_env.c \
			ms_change_dir.c \
			ms_split_whitespace.c \
			ms_error.c

SRC		= $(addprefix $(SDIR), $(SFILE))
SDIR	= ./

LFILE	= ./libft/libft.a
LIB		= -L./libft -lft
LDIR	= ./libft/

OFILE	= $(SRC:.c=.o)
OBJ		= $(addprefix $(ODIR), $(OFILE))
ODIR	= ./obj/

CC		= gcc
FLAG	= -Wall -Wextra -Werror
RM		= rm -rf
MC		= make -C

all: $(LFILE) $(NAME)

$(LFILE):
	@$(MC) $(LDIR) re

$(ODIR)%.o: %.c
	@mkdir -p $(ODIR)
	@$(CC) -c $(FLAG) $(INCL) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LIB)

clean:
	@$(MC) $(LDIR) clean
	@$(RM) $(ODIR)

fclean: clean
	@$(RM) $(LFILE)
	@$(RM) $(NAME)

re: fclean all
