/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 12:00:00 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/15 11:17:32 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Global key state (needed for hook callbacks) */
static t_keys	g_keys;

/**
 * key_press - Handle keyboard key press
 * @key_code: X11 key code
 *
 * Sets movement flags based on key press.
 */
static void	key_press(int key_code)
{
	if (key_code == 119 || key_code == 65362)
		g_keys.forward = true;
	if (key_code == 115 || key_code == 65364)
		g_keys.backward = true;
	if (key_code == 97 || key_code == 65361)
		g_keys.left = true;
	if (key_code == 100 || key_code == 65363)
		g_keys.right = true;
	if (key_code == 113)
		g_keys.rotate_left = true;
	if (key_code == 101)
		g_keys.rotate_right = true;
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
	key_press(key_code);
	return (0);
}

/**
 * get_global_keys - Return pointer to global key state
 *
 * Used internally for rendering to access key state.
 */
t_keys	*get_global_keys(void)
{
	return (&g_keys);
}
