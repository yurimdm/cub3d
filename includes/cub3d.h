/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:08:58 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/06 12:53:10 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "mlx.h"
# include "libft.h"

# define WIN_W 960
# define WIN_H 540
# define TEX_SIZE 64

# define MOVE_SPEED 0.01
# define ROT_SPEED 0.005
# define KEY_MAX 65536
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define WINDOW_TITLE "Cub3D"
# define ASSET_SIZE 32
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* Include OOP-style modules */
# include "key_handling.h"
# include "maps.h"
# include "player.h"
# include "raycasting.h"

/* Image structures */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_tex;

/* Main game structure */
typedef struct s_game
{
	t_player	player;
	t_map		map;
	t_ray		ray;
	void		*mlx;
	void		*win;
	t_img		frame;
	t_tex		tex[4];
	int			keys[KEY_MAX];
	int			running;
}	t_game;

/* Game initialization and management */
int		parse_scene(t_game *game, const char *path);
void	init_player(t_game *game);
void	update_player(t_game *game);
int		init_mlx(t_game *game);
int		load_textures(t_game *game);
void	render_frame(t_game *game);
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
int		close_game(void *param);
void	free_game(t_game *game);

/* Graphics utilities */
int		rgb_to_int(int r, int g, int b);
void	put_pixel(t_img *img, int x, int y, int color);
int		get_tex_color(t_tex *tex, int x, int y);

/* Map utilities */
int		is_wall(t_map *map, double x, double y);

/* Raycasting */
void	handle_rotation(t_game *game);
void	raycast(t_game *game);
void	prepare_ray(t_ray *ray, t_player *p, int x);
void	run_dda(t_ray *ray, t_map *map);

/* Hooks and main */
void	setup_hooks(t_game *game);
int		game_loop(void *param);
int		main(int argc, char **argv);

#endif
