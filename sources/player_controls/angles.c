/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deck <deck@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:57:02 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/16 19:07:12 by deck             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Normalize angle to [0, 2*PI) */
static float	normalize_angle(float angle)
{
	const float	two_pi = 2.0f * M_PI;

	while (angle < 0.0f)
		angle += two_pi;
	while (angle >= two_pi)
		angle -= two_pi;
	return (angle);
}

float	set_angle(t_player *player, float angle)
{
	if (!player)
		return (0.0f);
	player->angle = normalize_angle(angle);
	return (player->angle);
}

float	change_angle(t_player *player, float angle_change)
{
	if (!player)
		return (0.0f);
	player->angle = normalize_angle(player->angle + angle_change);
	return (player->angle);
}

void	player_debug_log(t_player *player)
{
	if (!player)
		return ;
	printf("Player pos: (%.2f, %.2f) angle: %.2fπ rad\n",
		player->xpos, player->ypos, player->angle / M_PI);
}

