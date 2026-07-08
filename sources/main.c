/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:09:02 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/08 15:27:07 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

void	setup_hooks(t_game *game);

static void	check_args(int argc)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putendl_fd("Usage: ./cub3D <map.cub>", 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_args(argc);
	ft_bzero(&game, sizeof(t_game));
	set_ctx_game(&game);
	parse_scene(&game, argv[1]);
	init_mlx(&game);
	load_textures(&game);
	init_player(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (EXIT_SUCCESS);
}
