NAME = pipex

SRC = src/cmds.c src/main.c src/utils.c src/ft_split_ps.c

LIBFT = includes/libft/libft.a

CC = gcc -g -Wall -Wextra -Werror

RM = rm -fr

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C includes/libft

$(NAME):$(OBJ) $(LIBFT)
	$(CC) $(OBJ) -Lincludes/libft -lft -o $(NAME)

%.o: %.c pipex.h
	$(CC) -c $< -o $@


clean:
	$(RM) $(OBJ)
	make -C  includes/libft clean

fclean: clean
	$(RM) $(NAME)
	make -C  includes/libft fclean

re: fclean all

.PHONY: all re fclean clean