NAME = minishell

SRCS = srcs/env_utils.c \
	srcs/input.c \
	srcs/prompt.c \
	srcs/env.c \
	srcs/execute_others.c \
	srcs/main.c \
	srcs/signals.c \
	srcs/utils.c \
	srcs/parser/eval_vars_and_unescape_in_lexema_chain.c \
	srcs/parser/exec_external_or_builtin_command.c \
	srcs/parser/parser_debug.c \
	srcs/parser/eval_vars_utils.c \
	srcs/parser/eval_with_fork_or_without.c \
	srcs/parser/get_command_type.c \
	srcs/parser/parser_lexema.c \
	srcs/parser/eval_with_pipe.c \
	srcs/parser/get_var_name.c \
	srcs/parser/is_var_name_symbol.c \
	srcs/parser/parser_lexema_2.c \
	srcs/parser/parser_lexema_3.c \
	srcs/parser/eval_with_pipe_or_without.c \
	srcs/parser/eval_with_redirect_or_without.c \
	srcs/parser/eval_with_redirect_or_without_2.c \
	srcs/parser/eval_with_redirect_or_without_3.c \
	srcs/parser/join_lexemas_without_spaces.c \
	srcs/parser/parser.c \
	srcs/parser/str_join_utils.c \
	srcs/parser/parser_check.c \
	srcs/parser/parser_lexema_chain.c \
	srcs/parser/remove_empty_elements.c \
	srcs/parser/t_redirects_close.c \
	srcs/commands/command_cd.c \
	srcs/commands/command_env.c \
	srcs/commands/command_export.c \
	srcs/commands/command_unset.c \
	srcs/commands/command_pwd.c \
	srcs/commands/export_utils.c \
	srcs/commands/command_echo.c \
	srcs/commands/command_exit.c \
	srcs/t_lexema/lexema_chain_copy.c \
	srcs/t_lexema/lexema_chain_free.c \
	srcs/t_lexema/t_lexema.c

HEADER = ./minishell.h

OBJS = $(SRCS:.c=.o)

FLAGS =-Wall -Wextra -Werror -O3

all: $(NAME)

$(NAME):
	@echo "\x1b[33m Preparing minishell...\x1b[0m"
	@make -C libft
	@gcc -o $(NAME) $(SRCS) libft/libft.a $(FLAGS)
	@echo "\x1b[32m Minishell is ready!\x1b[0m"

norm:
	@echo "\x1b[33m Sources NORM CHECK...\x1b[0m"
	@norminette srcs/*.c srcs/parser/*.c srcs/t_lexema/*.c srcs/commands/*.c
	@echo "\n\x1b[33m Headers NORM CHECK...\x1b[0m"
	@norminette srcs/minishell.h srcs/parser/parser.h
	@echo "\n\x1b[33m Libft NORM CHECK...\x1b[0m"
	@norminette libft/*.c libft/*.h

clean:
	@rm -rf $(OBJS)
	@make -C libft clean

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean
	@rm -rf test.txt

re: fclean all

test: re
	@if ! [ -d ./minishell-tester ]; then \
  		echo "\x1b[31m No tester directory! \x1b[0m"; \
  		echo "\x1b[31m STOP \x1b[0m"; \
  	else \
		touch test.txt ; \
		chmod a+rw test.txt ; \
		echo "test\nabc" >> ./test.txt ; \
		cd ./minishell-tester ; rm -f ./minishell ; cd .. ; \
		cp ./minishell ./minishell-tester/minishell ; \
		cd ./minishell-tester ; bash test.sh ; cd .. ; \
	fi

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

.PHONY:	all clean fclean re
