/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deck <deck@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 19:21:35 by ymazzett          #+#    #+#             */
/*   Updated: 2026/06/16 19:23:47 by deck             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H
# include "cub3d.h"

typedef struct s_ray
{
	float	ray_angle;
	float	ray_x;
	float	ray_y;
	float	distance;
}			t_ray;

#endif