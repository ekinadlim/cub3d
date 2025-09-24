NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP #-fsanitize=undefined #-g #comment out -pedantic -Wno-newline-eof
MLXFLAGS = -lX11 -lmlx -lXext
#MAKEFLAGS = -s

LIBFT_DIR = libft

OBJ_DIR = obj

LIBFT = $(LIBFT_DIR)/libft.a

SRC = 	main.c\
		parsing.c\
		arg_validation.c\
		get_map.c\
		get_map_size.c\
		get_color.c\
		get_image.c\
		get_player.c\
		check_map.c\
		helper.c\

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

DEPS = $(OBJ:.o=.d)

all: $(NAME)
	./$(NAME) maps/example.cub

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
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) maps/example.cub

.PHONY: all clean fclean re val