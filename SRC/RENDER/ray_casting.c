/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:06:58 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/31 14:03:41 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


double	wall_height(t_intersect *inter)
{
	double	projected_slice_height;

	projected_slice_height = (int)(TILE_SIZE / inter->distance * DIST_TO_PP); // % HEIGHT;

	if (projected_slice_height > HEIGHT)
	{
		return (HEIGHT);
	}
	return (projected_slice_height); //place wall in the middle so half of this is above middle and other half is below!
}


double	normalize_angle(double alpha)
{
	if (alpha <= 2 * M_PI || alpha >= 0)
		return (alpha);
	while (alpha > 2 * M_PI)
		(alpha) -= M_PI;
	while (alpha < 0)
		(alpha) += 2 * M_PI;
	return (alpha);
}

double	distance(t_tuple source, t_tuple destination) // there is a faster equation where dist(x)/cos(alpha)
{
	double	distance;

	distance = 0;
	distance = sqrt(pow((destination.x - source.x), 2) + pow((destination.y - source.y), 2));
	return (distance);
}

static char	check_tile(t_cube *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	return (data->map.data[map_y][map_x]);
}

static void	find_direction(t_intersect *inter, t_tuple ray, int flag)
{
	if (flag == 1)
	{
		if (ray.x >= 0)
			inter->side = WEST;
		else
			inter->side = EAST;
	}
	else
	{
		if (ray.y >= 0)
			inter->side = NORTH;
		else
			inter->side = SOUTH;
	}
}

t_intersect	find_intersection(t_cube *data, t_tuple ray, double alpha)
{
	t_tuple	pos;
	t_intersect	inter;

	pos.x = data->player.pos.x;
	pos.y = data->player.pos.y;
	while (pos.x >= 0 && pos.x <= TILE_SIZE * data->map.width && pos.y >= 0 && pos.y <= TILE_SIZE * data->map.height)
	{
		if ((int)pos.x % TILE_SIZE == 0 && check_tile(data, pos.x + ray.x, pos.y) == '1')
		{
			find_direction(&inter, ray, 1);
			break ;
		}
		else if ((int)pos.y % TILE_SIZE == 0 && check_tile(data, pos.x, pos.y + ray.y) == '1')
		{
			find_direction(&inter, ray, 2);
			break ;
		}
		pos.x += ray.x;
		pos.y += ray.y;
	}
	inter.x = pos.x;
	inter.y = pos.y;
	inter.distance = distance(pos, data->player.pos);
	inter.distance *= cos(fabs(data->player.alpha - alpha));
	return (inter);
}

t_intersect	*ray_casting_main(t_cube *data)
{
	t_intersect	*inter;
	int			i;
	double		angle;
	t_tuple		ray;

	inter = safe_malloc(sizeof(t_intersect), WIDTH * 2 + 1);
	if (inter == NULL)
		return (NULL);
	
	i = 0;
	while (i < WIDTH)
	{
		angle = normalize_angle(data->player.alpha + (FOV / 2) - (i * FOV / (WIDTH))); // current heading + left side of FOV - iterating angle to
		ray.x = cos(angle);
		ray.y = sin(angle);
		inter[i] = find_intersection(data, ray, angle);
		i++;
	}
	return (inter);
}
