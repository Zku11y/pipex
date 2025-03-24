NAME = pipex

SRC = src/cmds.c src/main.c src/utils.c src/ft_split_ps.c

LIBFT = includes/libft/libft.a

LIBFT_IN = includes/libft

CC = cc -g -Wall -Wextra -Werror

RM = rm -fr

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_IN)

$(NAME):$(OBJ) $(LIBFT)
	$(CC) $(OBJ) -o $(NAME) $(LIBFT)

# $(CC) $(OBJ) -L$(LIBFT_IN) -lft -o $(NAME)

%.o: %.c pipex.h
	$(CC) -c $< -o $@


clean:
	$(RM) $(OBJ)
	make -C  $(LIBFT_IN) clean

fclean: clean
	$(RM) $(NAME)
	make -C  $(LIBFT_IN) fclean

re: fclean all

.PHONY: all re fclean clean