/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:09:02 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/15 12:10:48 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop(void)
{
	return (0);
}

int	main(int argc, char **argv)
{
	static t_game	game;

	if (!game_init(argc, argv, &game))
		return (1);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_hook(game.win, 2, 1L << 0, key_hook, &game);
	mlx_loop_hook(game.mlx, render_all, &game);
	mlx_loop(game.mlx);
	return (0);
}
