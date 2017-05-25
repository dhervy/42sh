NAME = 42sh

CC = clang
CFLAGS = -Wall -Werror -Wextra

CPATH = core/
SRC = \
		core.c\
		env.c\
		env.2.c\
		env.utils.c\
		env.utils.2.c\
		paths.utils.c\
		builtins.utils.c\
		cd.c\
		errors.c\
		mexit.c\
		edl.clipboard.c\
		edl.string.utils.c\
		history.utils.c\
		core.utils.c\
		key.c\
		key.execute.c\
		key.execute.2.c\
		key.utils.c\
		move.c\
		move.utils.c\
		move2.c\
		term.c\
		term.utils.c\
		afd.process.c\
		afd.utils.c\
		exec.beta.c\
		exec.handlers.c\
		exec.heredoc.c\
		exec.left.redir.c\
		exec.pipe.c\
		exec.redir.c\
		exec.signals.c\
		exec.signals.utils.c\
		exec.simple.c\
		exec.utils.c\
		afd.load.c\
		check.dquotes.c\
		lexer.c\
		lexer.dquotes.c\
		lexer.dquotes2.c\
		lexer.dquotes.utils.c\
		lexer.list.c\
		lexer.list2.c\
		lexer.utils.c\
		lexer.utils2.c\
		node.utils.c\
		token.c\
		tree.create.c\
		tree.utils.c\
		tree.valid.c\
		errors.utils.c\
		print.utils.c\
		string.utils.c\
		string.utils2.c\
		tabs.utils.c\
		tabs.utils2.c\
		lexer.var_replace.c\
		lexer.clean_cmd.c\
		alias.import.c\
		edl.remake.c\
		history.c\
		history2.c\
		history3.c\
		history4.c\
		history.p_ex.c\
		history.p_ex2.c\
		history.p_ex3.c\
		history.p_ex4.c\
		autocomplet.c\
		autocomplet2.c\
		autocomplet3.c\
		autocomplet4.c\
		autocomplet5.c\
		read.c\
		move_updown.c\
		move_updown2.c\

OPATH = obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OPATH), $(OBJ))

.PHONY: all clean fclean re

all:		$(NAME)
			@printf "\e[38;5;198mready\e[0m\n"

$(NAME):	$(OBJS)
			@make -C libft
			@$(CC) $(CFLAGS) $(OBJS) -o$(NAME) -L libft -lft -lncurses
			@printf "\n"

$(OPATH)%.o:$(CPATH)%.c
			@mkdir -p $(OPATH)
			@printf "\e[38;5;245m●\e[0m"
			@$(CC) $(CFLAGS) -I includes -I libft/includes -c -o $@ $<

clean:
			@printf "\e[38;5;42mcleaned\e[0m\n"
			@make -C libft clean
			@rm -f $(OBJS)

fclean:		clean
			@make -C libft fclean
			@rm -f $(NAME)

re:			fclean	all
