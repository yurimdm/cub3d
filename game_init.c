/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 12:00:00 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/15 14:16:42 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	spawn_angle(char spawn_dir)
{
	if (spawn_dir == 'N')
		return (-M_PI_2);
	if (spawn_dir == 'S')
		return (M_PI_2);
	if (spawn_dir == 'W')
		return (M_PI);
	return (0.0f);
}

static int	setup_player(t_game *game)
{
	float	a;

	a = spawn_angle(game->map.spawn_dir);
	game->player = init_player(game->map.spawn_x, game->map.spawn_y, a);
	return (1);
}

/**
 * game_init - Initialize the game
 * @argc: argument count
 * @argv: argument vector (should contain map file path)
 * @game: pointer to game structure
 *
 * Initializes MLX, creates window, loads map, and sets up player.
 * Returns 1 on success, 0 on failure.
 */
int	game_init(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		return (ft_putstr_fd("Error: Usage: ./cub3d <map_file.cub>\n", 2), 0);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_putstr_fd("Error: MLX initialization failed\n", 2), 0);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_TITLE);
	if (!game->win)
		return (ft_putstr_fd("Error: Window creation failed\n", 2), 0);
	game->map.file_path = argv[1];
	if (!load_map(&game->map, argv[1]))
		return (ft_putstr_fd("Error: Map loading failed\n", 2), 0);
	return (setup_player(game));
}
