NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -std=gnu99

UNAME_S := $(shell uname -s)

MLX_DIR = ./mlx
MLX = $(MLX_DIR)/libmlx.a
OBJ_DIR = ./obj

ifeq ($(UNAME_S),Darwin)
MLX_LDFLAGS = -framework OpenGL -framework AppKit
else
MLX_LDFLAGS = -L./mlx -lmlx -lX11 -lXext -lm -lbsd
endif

SRCS = main.c \
	player_controls/player_init.c player_controls/movements.c player_controls/angles.c \
	raycast/raycast.c raycast/ray_dda.c \
	render/render.c \
	mlx_utils/init_mlx.c mlx_utils/textures.c mlx_utils/hooks.c mlx_utils/cleanup.c \
	utils/color.c \
	parser/parser.c parser/parser_utils.c parser/parser_elements.c \
	parser/parser_attrs.c parser/parser_map.c parser/parser_validate.c \
	libft/gnl/get_next_line.c libft/gnl/get_next_line_utils.c \
	libft/ft_atoi.c libft/ft_bzero.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_tolower.c \
	libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_memchr.c libft/ft_memcpy.c \
	libft/ft_memcmp.c libft/ft_memset.c libft/ft_strlcat.c libft/ft_toupper.c \
	libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strncmp.c libft/ft_calloc.c libft/ft_strrchr.c \
	libft/ft_memmove.c libft/ft_strdup.c libft/ft_strnstr.c libft/ft_strjoin.c libft/ft_putchar_fd.c \
	libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_strmapi.c \
	libft/ft_strtrim.c libft/ft_substr.c libft/ft_split.c libft/ft_itoa.c libft/ft_striteri.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

linux: $(MLX) $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) $(MLX) -L./mlx -lmlx -lX11 -lXext -lm -lbsd -o $(NAME)

$(NAME): $(MLX) $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) $(MLX) $(MLX_LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

$(MLX):
	@make -C $(MLX_DIR)

$(OBJ_DIR):
	mkdir -p $@
	mkdir -p $@/libft
	mkdir -p $@/libft/gnl
	mkdir -p $@/player_controls
	mkdir -p $@/parser
	mkdir -p $@/raycast
	mkdir -p $@/render
	mkdir -p $@/mlx_utils
	mkdir -p $@/utils

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

relinux: fclean linux

.PHONY: all linux clean fclean re relinux
