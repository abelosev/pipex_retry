NAME = pipex

CC = cc

CF = -Wall -Werror -Wextra

SRC = main.c \
		struct.c \
		child.c \
		wait.c \
		exit.c \
		get_args.c

OBJ = $(SRC:.c=.o)

LIB_DIR = printf
LIB = $(LIB_DIR)/libftprintf.a

INC = -I. -I$(LIB_DIR)/inc -I$(LIB_DIR)/libft

all: $(LIB) $(NAME)

$(LIB):
	make -C $(LIB_DIR)

$(NAME): $(OBJ)
	$(CC) $(CF) $(OBJ) $(LIB) -L$(LIB_DIR)/libft -lft -o $(NAME)

%.o : %.c
	$(CC) $(CF) $(INC) -c $< -o $@

clean :
	rm -rf $(OBJ)
	make -C $(LIB_DIR) clean

fclean :
	rm -rf $(NAME)
	rm -rf $(OBJ)
	make -C $(LIB_DIR) fclean

re : fclean all

.PHONY : all clean fclean re