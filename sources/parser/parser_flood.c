/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flood.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:30:00 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/10 18:30:00 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../libft/libft.h"

/*
** Flood-fill based validation.  Spaces (' ') and walls ('1') are treated
** as impassable so a map containing internal spaces is accepted, as long
** as no walkable cell can leak past the outer border of the grid.  A
** duplicate grid is used so the original map layout stays untouched.
*/

static void	free_grid_copy(char **copy)
{
	int	i;

	if (!copy)
		return ;
	i = 0;
	while (copy[i])
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

static char	**dup_grid(char **grid, int height)
{
	char	**copy;
	int		i;

	copy = ft_calloc((size_t)height + 1, sizeof(char *));
	if (!copy)
		error_exit("Memory error");
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(grid[i]);
		if (!copy[i])
		{
			free_grid_copy(copy);
			error_exit("Memory error");
		}
		i++;
	}
	return (copy);
}

static void	flood_fill(char **grid, int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		error_exit("Map is not closed by walls");
	if (grid[y][x] == '1' || grid[y][x] == ' ' || grid[y][x] == 'V')
		return ;
	grid[y][x] = 'V';
	flood_fill(grid, x + 1, y, map);
	flood_fill(grid, x - 1, y, map);
	flood_fill(grid, x, y + 1, map);
	flood_fill(grid, x, y - 1, map);
}

void	check_reachability(t_map *map)
{
	char	**copy;

	copy = dup_grid(map->grid, map->height);
	flood_fill(copy, map->player_x, map->player_y, map);
	free_grid_copy(copy);
}
