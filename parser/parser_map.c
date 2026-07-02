/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:14:27 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/02 17:14:27 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../libft/libft.h"

static int	count_map_lines(char **lines, int start)
{
	int	count;
	int	i;

	count = 0;
	i = start;
	while (lines[i] && !is_blank_line(lines[i]))
	{
		count++;
		i++;
	}
	while (lines[i])
	{
		if (!is_blank_line(lines[i]))
			error_exit("Empty line inside map or extra content after map");
		i++;
	}
	return (count);
}

static int	get_max_width(char **lines, int start, int count)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = 0;
	while (i < count)
	{
		len = (int)ft_strlen(lines[start + i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static char	*pad_line(const char *line, int width)
{
	char	*padded;
	int		len;
	int		i;

	padded = malloc((size_t)width + 1);
	if (!padded)
		error_exit("Memory error");
	len = (int)ft_strlen(line);
	i = 0;
	while (i < len)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < width)
		padded[i++] = ' ';
	padded[width] = '\0';
	return (padded);
}

void	extract_map(t_map *map, char **lines, int start)
{
	int	i;

	map->height = count_map_lines(lines, start);
	if (map->height == 0)
		error_exit("Empty map");
	map->width = get_max_width(lines, start, map->height);
	if (map->width < 3 || map->height < 3)
		error_exit("Map too small to be enclosed");
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		error_exit("Memory error");
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = pad_line(lines[start + i], map->width);
		i++;
	}
	map->grid[i] = NULL;
}
