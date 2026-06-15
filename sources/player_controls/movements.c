/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:57:04 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/15 15:52:35 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	init_player(int x, int y, float angle)
{
	t_player	player;

	player.xpos = (float)x;
	player.ypos = (float)y;
	player.angle = angle;
	player.move_speed = 0.1f;
	player.angle_speed = 5.0f;
	player.set_pos = set_pos;
	player.move_x = move_x;
	player.move_y = move_y;
	player.move_player = move_player;
	player.set_angle = set_angle;
	player.change_angle = change_angle;
	player.debug_log = debug_log;
	return (player);
}

t_bool	set_pos(t_player *player, int x, int y)
{
	player->xpos = (float)x;
	player->ypos = (float)y;
	return (true);
}

t_bool	move_x(t_player *player, t_map *map, float distance)
{
	float	new_x;
	float	new_y;

	new_x = player->xpos + cosf(player->angle) * distance;
	new_y = player->ypos + sinf(player->angle) * distance;
	if (is_wall(map, new_x, new_y))
		return (false);
	player->xpos = new_x;
	player->ypos = new_y;
	return (true);
}

t_bool	move_y(t_player *player, t_map *map, float distance)
{
	float	new_x;
	float	new_y;

	new_x = player->xpos - sinf(player->angle) * distance;
	new_y = player->ypos + cosf(player->angle) * distance;
	if (is_wall(map, new_x, new_y))
		return (false);
	player->xpos = new_x;
	player->ypos = new_y;
	return (true);
}

t_bool	move_player(t_player *player, t_map *map, float x_dis, float y_dis)
{
	float	new_x;
	float	new_y;

	new_x = player->xpos + x_dis;
	new_y = player->ypos + y_dis;
	if (is_wall(map, new_x, new_y))
		return (false);
	player->xpos = new_x;
	player->ypos = new_y;
	return (true);
}
