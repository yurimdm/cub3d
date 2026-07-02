/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:13:59 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/02 17:13:59 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../libft/libft.h"

int	is_map_line(const char *line)
{
	const char	*p;

	if (!line || !*line)
		return (0);
	p = line;
	while (*p == ' ' || *p == '\t')
		p++;
	if (!*p)
		return (0);
	while (*p)
	{
		if (*p != '0' && *p != '1' && *p != ' ' && *p != '\t'
			&& *p != 'N' && *p != 'S' && *p != 'E' && *p != 'W')
			return (0);
		p++;
	}
	return (1);
}

static int	match_id(const char *line, const char *id)
{
	size_t	idlen;

	idlen = ft_strlen(id);
	if (ft_strncmp(line, id, idlen) != 0)
		return (0);
	if (line[idlen] != ' ' && line[idlen] != '\t')
		return (0);
	return (1);
}

static void	dispatch_element(t_map *map, char *content)
{
	if (match_id(content, "NO"))
		parse_texture(&map->no_texture, content + 2);
	else if (match_id(content, "SO"))
		parse_texture(&map->so_texture, content + 2);
	else if (match_id(content, "WE"))
		parse_texture(&map->we_texture, content + 2);
	else if (match_id(content, "EA"))
		parse_texture(&map->ea_texture, content + 2);
	else if (match_id(content, "F"))
		parse_color(map->floor_color, &map->floor_set, content + 1);
	else if (match_id(content, "C"))
		parse_color(map->ceiling_color, &map->ceiling_set, content + 1);
	else
		error_exit("Invalid element identifier");
}

static int	all_elements_set(t_map *map)
{
	if (!map->no_texture || !map->so_texture)
		return (0);
	if (!map->we_texture || !map->ea_texture)
		return (0);
	if (!map->floor_set || !map->ceiling_set)
		return (0);
	return (1);
}

int	parse_elements(t_map *map, char **lines)
{
	int		i;
	char	*content;

	i = 0;
	while (lines[i])
	{
		strip_newline(lines[i]);
		if (is_blank_line(lines[i]))
		{
			i++;
			continue ;
		}
		content = skip_spaces(lines[i]);
		if (is_map_line(content))
		{
			if (!all_elements_set(map))
				error_exit("Missing scene elements before map");
			break ;
		}
		dispatch_element(map, content);
		i++;
	}
	if (!all_elements_set(map))
		error_exit("Missing scene elements");
	return (i);
}
