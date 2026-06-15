/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:08:58 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/15 18:03:43 by ymazzett         ###   ########.fr       */
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

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define WINDOW_TITLE "Cub3D"
# define ASSET_SIZE 32

typedef enum e_bool
{
	false,
	true
}	t_bool;

# include "key_handling.h"
# include "maps.h"
# include "player.h"

typedef struct s_ray
{
	float	ray_angle;
	float	ray_x;
	float	ray_y;
	float	distance;
}			t_ray;

typedef struct s_assets
{
	void	*north_wall;
	void	*south_wall;
	void	*west_wall;
	void	*east_wall;
}			t_assets;

typedef struct s_game
{
	t_player	player;
	t_map		map;
	t_ray		ray;
	void		*mlx;
	void		*win;
	t_assets	assets;
	t_keys		keys;

	int			(*game_init)(int argc, char **argv, struct s_game *game);
	int			(*render_all)(struct s_game *game);
	int			(*key_hook)(int key_code, struct s_game *game);
	int			(*close_game)(struct s_game *game);
}				t_game;

int			game_init(int argc, char **argv, t_game *game);
int			render_all(t_game *game);
int			key_hook(int key_code, t_game *game);
int			close_game(t_game *game);

void		put_circle_pixel(t_game *game, int cx, int cy, int x, int y, int color);
int			loop(void);
int			main(int argc, char **argv);

#endif
