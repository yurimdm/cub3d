/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 12:00:00 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/15 18:04:35 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/**
 * handle_player_movement - Update player position based on key input
 * @game: pointer to game structure
 *
 * Applies movement to player based on current key state.
 */
void	handle_player_movement(t_game *game)
{
	t_keys	*keys;

	keys = &game->keys;
	if (keys->forward)
		game->player.move_x(&game->player, &game->map,
			game->player.move_speed);
	if (keys->backward)
		game->player.move_x(&game->player, &game->map,
			-game->player.move_speed);
	if (keys->left)
		game->player.move_y(&game->player, &game->map,
			-game->player.move_speed);
	if (keys->right)
		game->player.move_y(&game->player, &game->map,
			game->player.move_speed);
	if (keys->rotate_left)
		game->player.change_angle(&game->player,
			-game->player.angle_speed * 0.017f);
	if (keys->rotate_right)
		game->player.change_angle(&game->player,
			game->player.angle_speed * 0.017f);
}

/**
 * render_all - Main game loop render function
 * @game: pointer to game structure
 *
 * Handles player movement based on key input and renders the frame.
 * Called every frame by MLX event loop.
 */
int	render_all(t_game *game)
{
	handle_player_movement(game);
	put_circle_pixel(game, (int)(game->player.xpos * 50),
		(int)(game->player.ypos * 50), 5, 5, 0xFF0000);
	// mlx_clear_window(game->mlx, game->win);
	mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF,
		"Cub3D - Raycasting Engine (WIP)");
	return (0);
}
