/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:16:07 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/02 17:16:07 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->running = 0;
	mlx_loop_end(game->mlx);
	return (0);
}

int	key_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		return (close_game(param));
	if (keycode >= 0 && keycode < KEY_MAX)
		game->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode >= 0 && keycode < KEY_MAX)
		game->keys[keycode] = 0;
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 1L << 17, close_game, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
