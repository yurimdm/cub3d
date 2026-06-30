/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deck <deck@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 12:00:00 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/16 19:00:36 by deck             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	unpress_all_keys(t_keys *keys)
{
	keys->forward = false;
	keys->backward = false;
	keys->left = false;
	keys->right = false;
	keys->rotate_left = false;
	keys->rotate_right = false;
}

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
	unpress_all_keys(keys);
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
	mlx_clear_window(game->mlx, game->win);
	game->player.player_debug_log(&game->player);
	put_circle_pixel(game, (int)(game->player.xpos * 50),
		(int)(game->player.ypos * 50), 10, 0xFF0000);
	mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF,
		"Cub3D - Raycasting Engine (WIP)");
	return (0);
}
