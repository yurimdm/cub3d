/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:59:10 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/02 12:51:27 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_circle_pixel(t_game *game, int cx, int cy, int size, int color)
{
	double	step;
	double	theta;
	double radius;
	int		x;
	int		y;

	radius = size;
	step = 1.0 / radius;
	theta = 0.0;
	while (theta < 2.0 * M_PI)
	{
		x = cx + (int)(radius * cos(theta));
		y = cy + (int)(radius * sin(theta));
		mlx_pixel_put(game->mlx, game->win, x, y, color);
		theta += step;
	}
}
