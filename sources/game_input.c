/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:19:05 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/02 17:19:06 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * key_press - Handle keyboard key press
 * @key_code: X11 key code
 *
 * Sets movement flags based on key press.
 */
static void	key_press(int key_code, t_game *game)
{
	if (key_code == KEY_W)
		game->keys.forward = true;
	if (key_code == KEY_S)
		game->keys.backward = true;
	if (key_code == KEY_A)
		game->keys.left = true;
	if (key_code == KEY_D)
		game->keys.right = true;
	if (key_code == KEY_ARROW_L)
		game->keys.rotate_left = true;
	if (key_code == KEY_ARROW_R)
		game->keys.rotate_right = true;
}

/**
 * key_hook - Handle keyboard input
 * @key_code: X11 key code
 * @game: pointer to game structure
 *
 * Handles key press and ESC to exit. Keys:
 * - W/A/S/D or Arrow keys for movement
 * - Q/E for rotation
 * - ESC to exit
 */
int	key_hook(int key_code, t_game *game)
{
	if (key_code == 65307)
		close_game(game);
	key_press(key_code, game);
	return (0);
}
