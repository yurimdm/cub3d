/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deck <deck@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 15:35:17 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/16 17:13:03 by deck             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "maps.h"
# include "cub3d.h"

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
	void			(*player_debug_log)(struct s_player *);
}			t_player;

t_player	init_player(int x, int y, float angle);
t_bool		set_pos(t_player *player, int x, int y);
t_bool		move_x(t_player *player, t_map *map, float distance);
t_bool		move_y(t_player *player, t_map *map, float distance);
t_bool		move_player(t_player *player, t_map *map, float x_dis, float y_dis);
float		set_angle(t_player *player, float angle);
float		change_angle(t_player *player, float angle_change);
void		player_debug_log(t_player *player);
void		destroy_player(t_player *player);

#endif
