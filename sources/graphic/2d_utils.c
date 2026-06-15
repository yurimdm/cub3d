/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:59:10 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/15 18:03:58 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_circle_pixel(t_game *game, int cx, int cy, int x, int y, int color)
{
	mlx_pixel_put(game->mlx, game->win, cx + x, cy + y, color);
	mlx_pixel_put(game->mlx, game->win, cx - x, cy + y, color);
	mlx_pixel_put(game->mlx, game->win, cx + x, cy - y, color);
	mlx_pixel_put(game->mlx, game->win, cx - x, cy - y, color);
	mlx_pixel_put(game->mlx, game->win, cx + y, cy + x, color);
	mlx_pixel_put(game->mlx, game->win, cx - y, cy + x, color);
	mlx_pixel_put(game->mlx, game->win, cx + y, cy - x, color);
	mlx_pixel_put(game->mlx, game->win, cx - y, cy - x, color);
}
