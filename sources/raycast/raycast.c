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

static void	compute_wall_dist(t_ray *ray, t_player *p)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - p->pos_x
				+ (1 - ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - p->pos_y
				+ (1 - ray->step_y) / 2.0) / ray->dir_y;
}

static void	set_tex_info(t_ray *ray, t_player *p)
{
	ray->line_height = (int)(WIN_H / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
	if (ray->side == 0)
		ray->wall_x = p->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = p->pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			ray->tex_num = 3;
		else
			ray->tex_num = 2;
	}
	else
	{
		if (ray->dir_y > 0)
			ray->tex_num = 1;
		else
			ray->tex_num = 0;
	}
}

static void	draw_column(t_game *game, t_ray *ray, int x)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		d;
	double	step;
	double	tex_pos;

	tex_x = (int)(ray->wall_x * (double)TEX_SIZE);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		tex_x = TEX_SIZE - tex_x - 1;
	step = 1.0 * TEX_SIZE / ray->line_height;
	d = ray->draw_start - WIN_H / 2 + ray->line_height / 2;
	tex_pos = (d) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_SIZE - 1);
		tex_pos += step;
		put_pixel(&game->frame, x, y,
			get_tex_color(&game->tex[ray->tex_num], tex_x, tex_y));
		y++;
	}
}

static void	cast_single_ray(t_game *game, int x)
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
