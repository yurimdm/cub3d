/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:11:46 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/02 17:11:46 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_a_dir(t_player *p, char dir_x, char dir_y)
{
	p->dir_x = dir_x;
	p->dir_y = dir_y;
}

static void	set_a_plane(t_player *p, double plane_x, double plane_y)
{
	p->plane_x = plane_x;
	p->plane_y = plane_y;
}

static void	set_direction(t_player *p, char dir)
{
	if (dir == 'N')
	{
		set_a_dir(p, 0, -1);
		set_a_plane(p, 0.66, 0);
	}
	else if (dir == 'S')
	{
		set_a_dir(p, 0, 1);
		set_a_plane(p, -0.66, 0);
	}
	else if (dir == 'E')
	{
		set_a_dir(p, 1, 0);
		set_a_plane(p, 0, 0.66);
	}
	else if (dir == 'W')
	{
		set_a_dir(p, -1, 0);
		set_a_plane(p, 0, -0.66);
	}
}

void	init_player(t_game *game)
{
	t_player	*p;

	p = &game->player;
	p->pos_x = game->map.player_x + 0.5;
	p->pos_y = game->map.player_y + 0.5;
	p->move_speed = MOVE_SPEED;
	p->rot_speed = ROT_SPEED;
	set_direction(p, game->map.player_dir);
}
