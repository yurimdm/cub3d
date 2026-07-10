/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:13:47 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/08 15:27:07 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

typedef struct s_parse_ctx
{
	t_game	*game;
	char	***lines;
}	t_parse_ctx;

void	set_ctx_game(t_game *game);
void	set_ctx_lines(char ***lines);
void	error_exit(const char *msg);
void	free_lines(char **lines);
char	**append_line(char **lines, char *line, int *count);
void	init_map_defaults(t_map *map);
void	strip_newline(char *line);
int		is_blank_line(const char *line);
char	*skip_spaces(char *s);
int		is_map_line(const char *line);

int		parse_elements(t_map *map, char **lines);
void	parse_texture(char **dst, char *s);
void	parse_color(int *rgb, int *set_flag, char *s);

void	extract_map(t_map *map, char **lines, int start);
void	validate_map(t_map *map);
void	check_reachability(t_map *map);

char	*get_next_line(int fd);

#endif
