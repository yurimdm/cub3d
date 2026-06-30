/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 19:00:00 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/10 19:00:00 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../libft/libft.h"

void	init_map_defaults(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->grid = NULL;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor_set = 0;
	map->ceiling_set = 0;
	map->player_count = 0;
	map->player_dir = 0;
	map->player_x = 0;
	map->player_y = 0;
}

char	**append_line(char **lines, char *line, int *count)
{
	char	**new_arr;
	int		i;

	new_arr = malloc(sizeof(char *) * (*count + 2));
	if (!new_arr)
	{
		free(line);
		free_lines(lines);
		return (NULL);
	}
	i = -1;
	while (++i < *count)
		new_arr[i] = lines[i];
	new_arr[*count] = line;
	new_arr[*count + 1] = NULL;
	free(lines);
	(*count)++;
	return (new_arr);
}

void	strip_newline(char *line)
{
	size_t	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
	{
		line[len - 1] = '\0';
		len--;
	}
}

int	is_blank_line(const char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

char	*skip_spaces(char *s)
{
	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}
