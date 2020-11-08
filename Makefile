NAME = minishell

SRCS = srcs/t_lexema/*.c srcs/parser/*.c srcs/commands/*.c srcs/*.c

HEADER = ./minishell.h

OBJS = $(SRCS:.c=.o)

FLAGS =-g

all: $(NAME)

$(NAME):
	@echo "\x1b[33m Preparing minishell...\x1b[0m"
	@make -C libft
	@gcc -o $(NAME) $(SRCS) libft/libft.a $(FLAGS)
	@touch test.txt
	@chmod a+rw test.txt
	@echo "test\nabc" >> ./test.txt
	@echo "\x1b[33m Minishell is ready!\x1b[0m"

norm:
	@echo "\x1b[33m Sources, headers, libft NORM CHECK...\x1b[0m"
	@norminette *.c minishell.h libft/*.c libft/*.h

clean:
	@rm -rf $(OBJS)
	@make -C libft clean

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean

re: fclean all

test: re
	@echo "Remove old minishell from test Folder"
	@cd ./minishell-tester ; rm -f ./minishell ; cd ..
	@echo "Copy minishell into test Folder"
	@cp ./minishell ./minishell-tester/minishell
	@echo "GoTo test Folder && Start tests"
	@cd ./minishell-tester ; bash test.sh

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

.PHONY:	all clean fclean re
