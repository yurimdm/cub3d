/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:57:04 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/30 20:00:00 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_wall(t_map *map, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (mx < 0 || my < 0 || mx >= map->width || my >= map->height)
		return (1);
	if (map->grid[my][mx] == '1' || map->grid[my][mx] == ' ')
		return (1);
	return (0);
}

static void	try_move(t_game *game, double nx, double ny)
{
	if (!is_wall(&game->map, nx, game->player.pos_y))
		game->player.pos_x = nx;
	if (!is_wall(&game->map, game->player.pos_x, ny))
		game->player.pos_y = ny;
}

static void	move_forward(t_game *game, int dir)
{
	double	speed;
	double	nx;
	double	ny;

	speed = game->player.move_speed * dir;
	nx = game->player.pos_x + game->player.dir_x * speed;
	ny = game->player.pos_y + game->player.dir_y * speed;
	try_move(game, nx, ny);
}

static void	strafe(t_game *game, int dir)
{
	double	speed;
	double	nx;
	double	ny;

	speed = game->player.move_speed * dir;
	nx = game->player.pos_x + game->player.plane_x * speed;
	ny = game->player.pos_y + game->player.plane_y * speed;
	try_move(game, nx, ny);
}

void	update_player(t_game *game)
{
	if (game->keys[KEY_W])
		move_forward(game, 1);
	if (game->keys[KEY_S])
		move_forward(game, -1);
	if (game->keys[KEY_A])
		strafe(game, -1);
	if (game->keys[KEY_D])
		strafe(game, 1);
}
