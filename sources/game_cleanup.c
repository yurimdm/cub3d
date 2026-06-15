/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 12:00:00 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/15 11:49:48 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map_grid(t_map *map)
{
	int	row;

	if (!map->grid)
		return ;
	row = 0;
	while (row < map->height)
	{
		free(map->grid[row]);
		row++;
	}
	free(map->grid);
	map->grid = NULL;
}

/**
 * close_game - Cleanup and exit the game
 * @game: pointer to game structure
 *
 * Frees all allocated resources and exits cleanly.
 */
int	close_game(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_map_grid(&game->map);
	if (game->map.file_path)
	{
		free(game->map.file_path);
		game->map.file_path = NULL;
	}
	exit(0);
	return (0);
}
