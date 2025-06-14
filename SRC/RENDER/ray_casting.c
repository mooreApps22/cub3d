/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:06:58 by mcoskune          #+#    #+#             */
/*   Updated: 2025/06/06 13:30:49 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	check_tile(t_cube *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_y < 0 || map_y >= data->map.height)
		return (' ');
	if (map_x < 0 || map_x >= data->map.width)
		return (' ');
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

bool	check_tile_find_direction(t_cube *data,
	t_tuple ray, t_tuple *pos, t_intersect *inter)
{
	if ((int)(*pos).x % TILE_SIZE == 0
		&& check_tile(data, (*pos).x + ray.x, (*pos).y) == '1')
	{
		find_direction(inter, ray, 1);
		return (false);
	}
	else if ((int)(*pos).y % TILE_SIZE == 0
		&& check_tile(data, (*pos).x, (*pos).y + ray.y) == '1')
	{
		find_direction(inter, ray, 2);
		return (false);
	}
	(*pos).x += ray.x;
	(*pos).y += ray.y;
	return (true);
}

t_intersect	find_intersection(t_cube *data, t_tuple ray, double alpha)
{
	t_tuple		pos;
	t_intersect	inter;

	pos.x = data->player.pos.x;
	pos.y = data->player.pos.y;
	while (pos.x >= 0 && pos.x <= TILE_SIZE * data->map.width
		&& pos.y >= 0 && pos.y <= TILE_SIZE * data->map.height)
	{
		if (!check_tile_find_direction(data, ray, &pos, &inter))
			break ;
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
		angle = normalize_angle(data->player.alpha
				+ (data->cam.fov / 2) - (i * data->cam.fov / (WIDTH)));
		ray.x = cos(angle);
		ray.y = sin(angle);
		inter[i] = find_intersection(data, ray, angle);
		i++;
	}
	return (inter);
}
