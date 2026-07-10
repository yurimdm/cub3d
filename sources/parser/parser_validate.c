/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:14:15 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/10 18:30:00 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../libft/libft.h"

/*
** The subject states that spaces are a valid part of the map and it is up
** to us to handle them.  We treat spaces as blocking cells (identical to
** walls for gameplay) and validate closure through a flood-fill starting
** from the player position.  This allows any map that is truly enclosed by
** walls, including maps that contain internal space "pillars".
*/

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_player_info(t_map *map, int x, int y, char c)
{
	map->player_count++;
	map->player_dir = c;
	map->player_x = x;
	map->player_y = y;
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
				set_player_info(map, x, y, c);
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
	check_reachability(map);
	map->grid[map->player_y][map->player_x] = '0';
}
