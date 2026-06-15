/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 15:39:39 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/15 16:16:32 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
# define MAPS_H
# include "cub3d.h"

typedef struct s_map
{
	int		fd;
	char	*file_path;
	int		width;
	int		height;
	char	**grid;
	int		spawn_x;
	int		spawn_y;
	char	spawn_dir;
	t_bool	(*file_to_grid)(struct s_map * m);
	t_bool	(*is_wall)(struct s_map * m, float x, float y);
	t_bool	(*load_map)(struct s_map * m, const char *fp);
}			t_map;

t_bool		file_to_grid(t_map *map);
t_bool		is_wall(t_map *map, float x, float y);
t_bool		load_map(t_map *map, const char *file_path);
void		map_init_spawn(t_map *map);
void		map_scan_spawn(t_map *map, int h);
void		map_set_default_spawn(t_map *map);

#endif
