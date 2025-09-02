NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP -g#comment out
MLXFLAGS = -lX11 -lmlx -lXext
#MAKEFLAGS = -s

LIBFT_DIR = libft

OBJ_DIR = obj

LIBFT = $(LIBFT_DIR)/libft.a

SRC = main.c parsing.c helper.c arg_validation.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

DEPS = $(OBJ:.o=.d)

all: $(NAME)
	./$(NAME) example.cub

$(NAME): $(LIBFT) $(OBJ)
	cc $(CFLAGS) $(MLXFLAGS) $(OBJ) $(LIBFT) -lm -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ) $(DEPS) $(OBJ_DIR)

fclean:
	make fclean -C $(LIBFT_DIR)
	rm -rf $(OBJ) $(DEPS) $(OBJ_DIR) $(NAME)

re: fclean all

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY: all clean fclean re val