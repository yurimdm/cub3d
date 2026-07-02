/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:14:15 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/02 17:14:15 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../libft/libft.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	validate_chars(t_map *map)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = map->grid[y][x];
			if (c != '0' && c != '1' && c != ' ' && !is_player_char(c))
				error_exit("Invalid character in map");
			if (is_player_char(c))
			{
				map->player_count++;
				map->player_dir = c;
				map->player_x = x;
				map->player_y = y;
			}
			x++;
		}
		y++;
	}
}

static int	neighbor_invalid(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (1);
	if (map->grid[y][x] == ' ')
		return (1);
	return (0);
}

static void	validate_borders(t_map *map)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = map->grid[y][x];
			if (c == '0' || is_player_char(c))
			{
				if (neighbor_invalid(map, x - 1, y)
					|| neighbor_invalid(map, x + 1, y)
					|| neighbor_invalid(map, x, y - 1)
					|| neighbor_invalid(map, x, y + 1))
					error_exit("Map is not closed by walls");
			}
			x++;
		}
		y++;
	}
}

void	validate_map(t_map *map)
{
	validate_chars(map);
	if (map->player_count != 1)
		error_exit("Map must contain exactly one player spawn (N/S/E/W)");
	validate_borders(map);
	map->grid[map->player_y][map->player_x] = '0';
}
