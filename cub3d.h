/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:08:58 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/02 16:57:00 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_W 960
# define WIN_H 540
# define TEX_SIZE 64

# define MOVE_SPEED 0.01
# define ROT_SPEED 0.005
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_MAX 65536

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

typedef struct s_map
{
	int		width;
	int		height;
	char	**grid;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	int		floor_set;
	int		ceiling_set;
	int		player_count;
	char	player_dir;
	int		player_x;
	int		player_y;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
}	t_ray;

typedef struct s_game
{
	t_player	player;
	t_map		map;
	void		*mlx;
	void		*win;
	t_img		frame;
	t_tex		tex[4];
	int			keys[KEY_MAX];
	int			running;
}	t_game;

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
int		rgb_to_int(int r, int g, int b);
void	put_pixel(t_img *img, int x, int y, int color);
int		get_tex_color(t_tex *tex, int x, int y);
int		is_wall(t_map *map, double x, double y);
void	handle_rotation(t_game *game);
void	raycast(t_game *game);
void	prepare_ray(t_ray *ray, t_player *p, int x);
void	run_dda(t_ray *ray, t_map *map);
void	setup_hooks(t_game *game);
int		game_loop(void *param);

#endif
