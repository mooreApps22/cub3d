/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:48:12 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/23 17:37:13 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

double	normalize_angle(double alpha)
{
	if (alpha <= M_PI || alpha >= -M_PI)
		return ;
	while (alpha >= M_PI)
		(alpha) -= M_PI;
	while (alpha <= -M_PI)
		(alpha) += M_PI;
}

double	distance(t_tuple source, t_tuple destination)
{
	double	distance;

	distance = 0;
	distance = sqrt(pow((destination.x - source.x), 2) + pow((destination.y - source.y), 2));
	return (distance);
}


t_tuple	ray_create(double x, double y)
{
	t_tuple ray;

	ray.x = x;
	ray.y = y;
}
static char	check_map_zone(t_cube *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	return (data->map_data.map[map_y][map_x]);
}

// static double	tuple_dot(t_tuple tup1, t_tuple tup2)
// {
// 	return (tup1.x * tup2.x + tup1.y* tup2.y);
// }

static t_dir	find_direction(t_cube *data, double x, double y, t_tuple ray)
{
	t_tuple	north;
	t_tuple	south;

	north = ray_create(0, -1);
	south = ray_create(0, 1);
	if (ray.x == 0.0 && ray.y > 0.0)
		return (NORTH);
	else if (ray.x == 0.0 && ray.y < 0.0)
		return (SOUTH);
	else if (ray.x > 0.0 && ray.y == 0.0)
		return (WEST);
	else if (ray.x < 0.0 && ray.y == 0.0)
		return (EAST);
	else if (ray.x > 0.0 && ray.y > 0.0 && ((int)x % TILE_SIZE > 2))
		return (NORTH);
	else if (ray.x > 0.0 && ray.y > 0.0)
		return (WEST);
	else if (ray.x > 0.0 && ray.y < 0.0 && ((int)x % TILE_SIZE > 2))
		return (SOUTH);
	else if (ray.x > 0.0 && ray.y < 0.0)
		return (WEST);
	else if (ray.x < 0.0 && ray.y > 0.0 && ((int)x % TILE_SIZE > 2))
		return (NORTH);
	else if (ray.x < 0.0 && ray.y > 0.0)
		return (EAST);
	else if (ray.x < 0.0 && ray.y < 0.0 && ((int)x % TILE_SIZE > 2))
		return (SOUTH);
	else if (ray.x < 0.0 && ray.y < 0.0)
		return (EAST);
	else
		return (NORTH);
}

static void	find_intersection(t_cube *data, t_intersect ***intersect, t_tuple ray)
{
	t_intersect	*inter;
	double	x;
	double	y;

	x = data->player.x_pos;
	y = data->player.y_pos;
	while (true)
	{
		if (check_map_zone(data, x, y) == '1')
		{
			inter = safe_malloc(sizeof(t_intersect), 1);
			inter->x = x;
			inter->y = y;
			inter->side = find_direction(data, x, y, ray);
			add_to_dptr((void ***)intersect, (void *)inter);
			return ;
		}
		x += ray.x;
		y += ray.y;
	}
}

t_intersect	*intersection_point(t_cube *data)
{
	t_tuple	**intersection;
	double	theta;
	double	beta;
	t_tuple	ray;

	theta = normalize_angle(data->player.alpha + FOV / 2);
	beta = normalize_angle(data->player.alpha - FOV / 2);
	intersection = NULL;
	while (theta != beta)
	{
		ray.x = cos(theta);
		ray.y = sin(theta);
		find_intersection(data, &intersection, ray);
		theta -= TURN_SIZE;
	}
	return (intersection);
}