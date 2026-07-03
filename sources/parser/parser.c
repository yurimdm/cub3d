/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:14:04 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/02 17:14:04 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cub3d.h"
#include <fcntl.h>

void	error_exit(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd((char *)msg, 2);
	exit(EXIT_FAILURE);
}

void	free_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

static int	has_cub_extension(const char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".cub", 4) == 0);
}

static char	**read_all_lines(int fd)
{
	char	**lines;
	char	*line;
	int		count;

	count = 0;
	lines = ft_calloc(1, sizeof(char *));
	if (!lines)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		lines = append_line(lines, line, &count);
		if (!lines)
			return (NULL);
		line = get_next_line(fd);
	}
	return (lines);
}

int	parse_scene(t_game *game, const char *path)
{
	char	**lines;
	int		fd;
	int		map_start;
	int		i;

	init_map_defaults(&game->map);
	if (!has_cub_extension(path))
		error_exit("File must have .cub extension");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open scene file");
	lines = read_all_lines(fd);
	close(fd);
	if (!lines)
		error_exit("Failed to read scene file");
	i = -1;
	while (lines[++i])
		strip_newline(lines[i]);
	map_start = parse_elements(&game->map, lines);
	extract_map(&game->map, lines, map_start);
	validate_map(&game->map);
	free_lines(lines);
	return (0);
}
