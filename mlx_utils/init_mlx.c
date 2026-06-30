/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 20:00:00 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/30 20:00:00 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../parser/parser.h"

static void	setup_img(t_img *img, void *mlx, int w, int h)
{
	img->img = mlx_new_image(mlx, w, h);
	if (!img->img)
		error_exit("Failed to create MLX image");
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("Failed to initialize MLX");
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3D");
	if (!game->win)
		error_exit("Failed to create MLX window");
	setup_img(&game->frame, game->mlx, WIN_W, WIN_H);
	game->running = 1;
	return (0);
}
