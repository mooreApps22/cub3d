/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:06:58 by mcoskune          #+#    #+#             */
/*   Updated: 2025/06/03 15:12:21 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

double	wall_height(t_intersect *inter, t_cube *data)
{
	return (TILE_SIZE / inter->distance * data->cam.dist_to_pp);
}

double	normalize_angle(double alpha)
{
	if (alpha >= 0 && alpha <= 2 * M_PI)
		return (alpha);
	while (alpha > 2 * M_PI)
		(alpha) -= 2 * M_PI;
	while (alpha < 0)
		(alpha) += 2 * M_PI;
	return (alpha);
}

double	distance(t_tuple source, t_tuple destination) // dist(x)/cos(alpha)
{
	double	distance;

	distance = 0;
	distance = sqrt(pow((destination.x - source.x), 2)
			+ pow((destination.y - source.y), 2));
	return (distance);
}
