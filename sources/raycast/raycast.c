/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:11:23 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/02 17:11:23 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast(t_game *game);

void	compute_wall_dist(t_ray *ray, t_player *p)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - p->pos_x
				+ (1 - ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - p->pos_y
				+ (1 - ray->step_y) / 2.0) / ray->dir_y;
}

void	cast_single_ray(t_game *game, int x)
{
	t_ray	ray;

	prepare_ray(&ray, &game->player, x);
	run_dda(&ray, &game->map);
	compute_wall_dist(&ray, &game->player);
	set_tex_info(&ray, &game->player);
	draw_column(game, &ray, x);
}

void	raycast(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		cast_single_ray(game, x);
		x++;
	}
}
