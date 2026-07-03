/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:57:02 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/03 17:26:43 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_player(t_game *game, double rot)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_r;
	double	sin_r;

	cos_r = cos(rot);
	sin_r = sin(rot);
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos_r
		- game->player.dir_y * sin_r;
	game->player.dir_y = old_dir_x * sin_r
		+ game->player.dir_y * cos_r;
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos_r
		- game->player.plane_y * sin_r;
	game->player.plane_y = old_plane_x * sin_r
		+ game->player.plane_y * cos_r;
}

void	handle_rotation(t_game *game)
{
	if (game->keys[KEY_LEFT])
		rotate_player(game, -game->player.rot_speed);
	if (game->keys[KEY_RIGHT])
		rotate_player(game, game->player.rot_speed);
}
