/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 08:28:43 by yurimdm           #+#    #+#             */
/*   Updated: 2026/06/15 11:49:55 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_init_spawn(t_map *map)
{
	map->spawn_x = -1;
	map->spawn_y = -1;
	map->spawn_dir = '\0';
}

void	map_scan_spawn(t_map *map, int h)
{
	int		x;
	char	c;

	x = 0;
	while (x < map->width)
	{
		c = map->grid[h][x];
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			map->spawn_x = x;
			map->spawn_y = h;
			map->spawn_dir = c;
			map->grid[h][x] = '0';
		}
		x++;
	}
}

void	map_set_default_spawn(t_map *map)
{
	map->spawn_x = 1;
	map->spawn_y = 1;
	map->spawn_dir = 'E';
}
