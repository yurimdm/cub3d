/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:08:58 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/10 19:26:11 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_player
{
	float	xpos;
	float	ypos;
	float	angle;
	float	move_speed;
	float	angle_speed;

	int		(*set_pos)(struct s_player *, int, int);
	t_bool	(*move_x)(struct s_player *, float);
	t_bool	(*move_y)(struct s_player *, float);
	t_bool	(*move_player)(struct s_player * p, float x, float y);
	float	(*set_angle)(struct s_player *, float);
	float	(*change_angle)(struct s_player *, float);
	void	(*debug_log)(struct s_player *);
}			t_player;

t_player	init_player(int x, int y, float angle);
int			set_pos(t_player *player, int x, int y);
t_bool		move_x(t_player *player, float distance);
t_bool		move_y(t_player *player, float distance);
t_bool		move_player(t_player *player, float x_dis, float y_dis);
float		set_angle(t_player *player, float angle);
float		change_angle(t_player *player, float angle_change);
void		debug_log(t_player *player);

typedef struct s_map
{
	int		fd;
	char	*file_path;
	int		width;
	int		height;
	char	**grid;
	t_bool	(*file_to_grid)(struct s_map * m);
	t_bool	(*is_wall)(struct s_map * m, float x, float y);
	t_bool	(*load_map)(struct s_map * m, const char *fp);
}			t_map;

t_bool		file_to_grid(t_map *map);
t_bool		is_wall(t_map *map, float x, float y);
t_bool		load_map(t_map *map, const char *file_path);

typedef struct s_ray
{
	float	ray_angle;
	float	ray_x;
	float	ray_y;
	float	distance;
}				t_ray;

typedef struct s_game
{
	t_player	player;
	t_map		map;
	t_ray		ray;
}				t_game;

#endif
