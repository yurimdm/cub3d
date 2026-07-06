/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 20:20:00 by ymazzett          #+#    #+#             */
/*   Updated: 2026/07/06 20:20:00 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cub3d.h"

/*
** Cleanup context used by error_exit() to release everything that has
** been allocated so far before terminating the program.  Because the
** cub3D subject forbids file-scope globals, the context lives as a
** function-local static and is reached through the ctx_ptr() accessor.
*/
static t_parse_ctx	*ctx_ptr(void)
{
	static t_parse_ctx	ctx;

	return (&ctx);
}

void	set_ctx_game(t_game *game)
{
	ctx_ptr()->game = game;
}

void	set_ctx_lines(char ***lines)
{
	ctx_ptr()->lines = lines;
}

void	error_exit(const char *msg)
{
	t_parse_ctx	*ctx;

	ctx = ctx_ptr();
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd((char *)msg, 2);
	if (ctx->lines && *ctx->lines)
	{
		free_lines(*ctx->lines);
		*ctx->lines = NULL;
	}
	if (ctx->game)
		free_game(ctx->game);
	exit(EXIT_FAILURE);
}
