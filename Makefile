NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -lm

SRC_DIR = srcs
OBJ_DIR = obj
LIBFT_DIR = libft
MLX_DIR = mlx
ASSETS_DIR = assets
MAPS_DIR = maps

CUB3D =	srcs/check.c srcs/get_next_line.c srcs/images.c srcs/main.c \
			srcs/make_char.c srcs/make_map.c srcs/render.c srcs/utils.c \
			srcs/raycast.c

OBJS = $(CUB3D:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11

INCLUDES = -I/usr/include -Imlx -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	
$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re bonus
