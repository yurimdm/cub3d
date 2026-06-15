/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazzett <ymazzett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:00:41 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/15 16:11:43 by ymazzett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_HANDLING_H
# define KEY_HANDLING_H
# include "cub3d.h"

# ifdef __linux__
#  define MY_OS 'L'
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ARROW_L 65361
#  define KEY_ARROW_R 65363
#  define KEY_ARROW_U 65362
#  define KEY_ARROW_D 65364
#  define KEY_ESC 65307

static inline void	destroy_display(void *mlx)
{
	mlx_destroy_display(mlx);
}

# else
#  define MY_OS 'M'
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ARROW_L 123
#  define KEY_ARROW_R 124
#  define KEY_ARROW_U 126
#  define KEY_ARROW_D 125
#  define KEY_ESC 53

static inline void	destroy_display(void *mlx)
{
	(void)mlx;
}

# endif

typedef struct s_keys
{
	t_bool	forward;
	t_bool	backward;
	t_bool	left;
	t_bool	right;
	t_bool	rotate_left;
	t_bool	rotate_right;
}	t_keys;

#endif
