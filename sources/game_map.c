/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:19:09 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/02 17:19:12 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const char	*g_hard_map[] = {
	"1111111111",
	"1000000001",
	"1000000001",
	"1000110001",
	"1000000001",
	"1010000001",
	"1000000N01",
	"1000000001",
	"1000000001",
	"1111111111",
};

t_bool	file_to_grid(t_map *map)
{
	(void)map;
	return (true);
}

t_bool	is_wall(t_map *map, float x, float y)
{
	int	gx;
	int	gy;

	if (!map || !map->grid)
		return (true);
	gx = (int)floorf(x);
	gy = (int)floorf(y);
	if (gx < 0 || gy < 0 || gy >= map->height || gx >= map->width)
		return (true);
	if (map->grid[gy][gx] == '1')
		return (true);
	return (false);
}

t_bool	load_map(t_map *map, const char *file_path)
{
	int	h;

	(void)file_path;
	if (!map)
		return (false);
	map->height = 10;
	map->width = 10;
	map->grid = (char **)malloc(sizeof(char *) * map->height);
	if (!map->grid)
		return (false);
	map_init_spawn(map);
	h = 0;
	while (h < map->height)
	{
		map->grid[h] = ft_strdup(g_hard_map[h]);
		map_scan_spawn(map, h);
		h++;
	}
	if (map->spawn_dir == '\0')
		map_set_default_spawn(map);
	return (true);
}
