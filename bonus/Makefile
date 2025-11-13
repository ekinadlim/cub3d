NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP #-g -fsanitize=undefined -pedantic -Wno-newline-eof #comment out
MLXFLAGS = -lX11 -lmlx -lXext
#MAKEFLAGS = -s

LIBFT_DIR = ../libft

OBJ_DIR = obj

LIBFT = $(LIBFT_DIR)/libft.a

SRC = 	main_bonus.c\
		init_bonus.c\
		raycasting_bonus.c\
		raycasting_utils_bonus.c\
		rendering_bonus.c\
		rendering_utils_bonus.c\
		input_bonus.c\
		movement_1_bonus.c\
		movement_2_bonus.c\
		movement_3_bonus.c\
		player_rotation_bonus.c\
		minimap_bonus.c\
		parsing_bonus.c\
		arg_validation_bonus.c\
		get_elements_bonus.c\
		get_map_bonus.c\
		get_map_size_bonus.c\
		get_color_bonus.c\
		get_images_bonus.c\
		get_player_bonus.c\
		check_map_bonus.c\
		helper_bonus.c\
		cleanup_bonus.c\
		doors_bonus.c\
		flashlight_bonus.c\

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

DEPS = $(OBJ:.o=.d)

all: $(NAME)

bonus: $(NAME)

FORCE:

$(NAME): $(LIBFT) $(OBJ)
	cc $(CFLAGS) $(MLXFLAGS) $(OBJ) $(LIBFT) -lm -o $(NAME)

$(LIBFT): FORCE
	@make -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean:
	make fclean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR) $(NAME)

re: fclean all

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME) maps/example.cub

.PHONY: all clean fclean re bonus FORCE val