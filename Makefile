NAME = pipex

SRC = src/in_cmd1.c src/main.c src/utils.c cmd_ps/ft_split_ps.c cmd_ps/misc.c

LIBFT = includes/libft/libft.a

CC = gcc -g

RM = rm -fr

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C includes/libft

$(NAME):$(OBJ) $(LIBFT)
	@echo "Linking pipex..."
	$(CC) $(OBJ) -Lincludes/libft -lft -o $(NAME)

%.o: %.c
	@echo "Compiling: $< -> $@"
	$(CC) -c $< -o $@


clean:
	$(RM) $(OBJ)
	make -C  includes/libft clean

fclean: clean
	$(RM) $(NAME)
	make -C  includes/libft fclean

re: fclean all

.PHONY: all re fclean clean