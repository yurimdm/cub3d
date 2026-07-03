/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:16:18 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/02 17:16:18 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../parser/parser.h"

static void	load_single_tex(t_game *game, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		error_exit("Failed to load texture");
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
}

int	load_textures(t_game *game)
{
	load_single_tex(game, &game->tex[0], game->map.no_texture);
	load_single_tex(game, &game->tex[1], game->map.so_texture);
	load_single_tex(game, &game->tex[2], game->map.we_texture);
	load_single_tex(game, &game->tex[3], game->map.ea_texture);
	return (0);
}
