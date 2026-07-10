NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g 

UNAME_S := $(shell uname -s)

MLX_DIR = ./mlx
MLX = $(MLX_DIR)/libmlx.a
OBJ_DIR = ./obj

ifeq ($(UNAME_S),Darwin)
MLX_LDFLAGS = -framework OpenGL -framework AppKit
else
MLX_LDFLAGS = -L./mlx -lmlx -lX11 -lXext -lm -lbsd
endif

SRCS = sources/main.c \
	sources/player_controls/player_init.c sources/player_controls/movements.c sources/player_controls/angles.c \
	sources/raycast/raycast.c sources/raycast/raycast_utils.c sources/raycast/ray_dda.c \
	sources/render/render.c \
	sources/mlx_utils/init_mlx.c sources/mlx_utils/textures.c sources/mlx_utils/hooks.c sources/mlx_utils/cleanup.c \
	sources/utils/color.c \
	sources/parser/parser.c sources/parser/parser_error.c sources/parser/parser_utils.c sources/parser/parser_elements.c \
	sources/parser/parser_attrs.c sources/parser/parser_map.c sources/parser/parser_validate.c \
	sources/parser/parser_flood.c \
	sources/libft/gnl/get_next_line.c sources/libft/gnl/get_next_line_utils.c \
	sources/libft/ft_atoi.c sources/libft/ft_bzero.c sources/libft/ft_isalnum.c sources/libft/ft_isalpha.c sources/libft/ft_tolower.c \
	sources/libft/ft_isascii.c sources/libft/ft_isdigit.c sources/libft/ft_isprint.c sources/libft/ft_memchr.c sources/libft/ft_memcpy.c \
	sources/libft/ft_memcmp.c sources/libft/ft_memset.c sources/libft/ft_strlcat.c sources/libft/ft_toupper.c \
	sources/libft/ft_strlcpy.c sources/libft/ft_strlen.c sources/libft/ft_strncmp.c sources/libft/ft_calloc.c sources/libft/ft_strrchr.c \
	sources/libft/ft_memmove.c sources/libft/ft_strdup.c sources/libft/ft_strnstr.c sources/libft/ft_strjoin.c sources/libft/ft_putchar_fd.c \
	sources/libft/ft_putstr_fd.c sources/libft/ft_putendl_fd.c sources/libft/ft_putnbr_fd.c sources/libft/ft_strmapi.c \
	sources/libft/ft_strtrim.c sources/libft/ft_substr.c sources/libft/ft_split.c sources/libft/ft_itoa.c sources/libft/ft_striteri.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(MLX) $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) $(MLX) $(MLX_LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -I./includes -I./sources/parser -I./sources/libft -I$(MLX_DIR) -c $< -o $@

$(MLX):
	@make -C $(MLX_DIR)

$(OBJ_DIR):
	mkdir -p $@
	mkdir -p $@/sources
	mkdir -p $@/sources/libft
	mkdir -p $@/sources/libft/gnl
	mkdir -p $@/sources/player_controls
	mkdir -p $@/sources/parser
	mkdir -p $@/sources/raycast
	mkdir -p $@/sources/render
	mkdir -p $@/sources/mlx_utils
	mkdir -p $@/sources/utils

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all linux clean fclean re relinux
