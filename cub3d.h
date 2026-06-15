/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:08:58 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/15 15:26:09 by ymazzett         ###   ########.fr       */
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
# include "libft/libft.h"

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define WINDOW_TITLE "Cub3D"
# define ASSET_SIZE 32

# ifdef __linux__
#  define MY_OS 'L'
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ESC 65307

static inline void	destroy_display(void *mlx)
{
	mlx_destroy_display(mlx);
}

# else
#  define MY_OS 'M'
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53

static inline void	destroy_display(void *mlx)
{
	(void)mlx;
}

# endif

typedef struct s_map	t_map;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_keys
{
	t_bool	forward;
	t_bool	backward;
	t_bool	left;
	t_bool	right;
	t_bool	rotate_left;
	t_bool	rotate_right;
}	t_keys;

typedef struct s_player
{
	float			xpos;
	float			ypos;
	float			angle;
	float			move_speed;
	float			angle_speed;

	struct s_player	(*init_player)(int x, int y, float angle);
	void			(*destroy_player)(struct s_player *player);

	t_bool			(*set_pos)(struct s_player *, int x, int y);
	t_bool			(*move_x)(struct s_player *, t_map *, float distance);
	t_bool			(*move_y)(struct s_player *, t_map *, float distance);
	t_bool			(*move_player)\
(struct s_player *, t_map *, float x, float y);
	float			(*set_angle)(struct s_player *, float);
	float			(*change_angle)(struct s_player *, float);
	void			(*debug_log)(struct s_player *);
}			t_player;

t_player	init_player(int x, int y, float angle);
t_bool		set_pos(t_player *player, int x, int y);
t_bool		move_x(t_player *player, t_map *map, float distance);
t_bool		move_y(t_player *player, t_map *map, float distance);
t_bool		move_player(t_player *player, t_map *map, float x_dis, float y_dis);
float		set_angle(t_player *player, float angle);
float		change_angle(t_player *player, float angle_change);
void		debug_log(t_player *player);
void		destroy_player(t_player *player);

typedef struct s_map
{
	int		fd;
	char	*file_path;
	int		width;
	int		height;
	char	**grid;
	int		spawn_x;
	int		spawn_y;
	char	spawn_dir;
	t_bool	(*file_to_grid)(struct s_map * m);
	t_bool	(*is_wall)(struct s_map * m, float x, float y);
	t_bool	(*load_map)(struct s_map * m, const char *fp);
}			t_map;

t_bool		file_to_grid(t_map *map);
t_bool		is_wall(t_map *map, float x, float y);
t_bool		load_map(t_map *map, const char *file_path);
void		map_init_spawn(t_map *map);
void		map_scan_spawn(t_map *map, int h);
void		map_set_default_spawn(t_map *map);

typedef struct s_ray
{
	float	ray_angle;
	float	ray_x;
	float	ray_y;
	float	distance;
}				t_ray;

typedef struct s_assets
{
	void	*north_wall;
	void	*south_wall;
	void	*west_wall;
	void	*east_wall;
}				t_assets;

typedef struct s_game
{
	t_player	player;
	t_map		map;
	t_ray		ray;
	void		*mlx;
	void		*win;
	t_assets	assets;

	int			(*game_init)(int argc, char **argv, struct s_game *game);
	int			(*render_all)(struct s_game *game);
	int			(*key_hook)(int key_code, struct s_game *game);
	int			(*close_game)(struct s_game *game);
}				t_game;

int			game_init(int argc, char **argv, t_game *game);
int			render_all(t_game *game);
int			key_hook(int key_code, t_game *game);
int			close_game(t_game *game);

int			loop(void);
int			main(int argc, char **argv);

#endif
