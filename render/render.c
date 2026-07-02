/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:11:34 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/02 17:11:34 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	raycast(t_game *game);

static void	fill_rect(t_img *img, int y0, int y1, int color)
{
	int	x;
	int	y;

	y = y0;
	while (y < y1)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_background(t_game *game)
{
	int	ceil;
	int	floor;

	ceil = rgb_to_int(game->map.ceiling_color[0],
			game->map.ceiling_color[1], game->map.ceiling_color[2]);
	floor = rgb_to_int(game->map.floor_color[0],
			game->map.floor_color[1], game->map.floor_color[2]);
	fill_rect(&game->frame, 0, WIN_H / 2, ceil);
	fill_rect(&game->frame, WIN_H / 2, WIN_H, floor);
}

void	render_frame(t_game *game)
{
	update_player(game);
	handle_rotation(game);
	draw_background(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}

int	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game->running)
		return (0);
	render_frame(game);
	return (0);
}
