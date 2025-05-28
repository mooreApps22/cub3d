/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:48:12 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/28 17:10:58 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"




// t_tuple	ray_create(double x, double y)
// {
// 	t_tuple ray;

// 	ray.x = x;
// 	ray.y = y;
// }


// static double	tuple_dot(t_tuple tup1, t_tuple tup2)
// {
// 	return (tup1.x * tup2.x + tup1.y* tup2.y);
// }

// static t_dir	find_direction(t_cube *data, double x, double y, t_tuple ray)
// {
// 	if (ray.x == 0.0 && ray.y > 0.0)
// 		return (NORTH);
// 	else if (ray.x == 0.0 && ray.y < 0.0)
// 		return (SOUTH);
// 	else if (ray.x > 0.0 && ray.y == 0.0)
// 		return (WEST);
// 	else if (ray.x < 0.0 && ray.y == 0.0)
// 		return (EAST);
// 	else if (ray.x > 0.0 && ray.y > 0.0 && ((int)x % TILE_SIZE > 2))
// 		return (NORTH);
// 	else if (ray.x > 0.0 && ray.y > 0.0)
// 		return (WEST);
// 	else if (ray.x > 0.0 && ray.y < 0.0 && ((int)x % TILE_SIZE > 2))
// 		return (SOUTH);
// 	else if (ray.x > 0.0 && ray.y < 0.0)
// 		return (WEST);
// 	else if (ray.x < 0.0 && ray.y > 0.0 && ((int)x % TILE_SIZE > 2))
// 		return (NORTH);
// 	else if (ray.x < 0.0 && ray.y > 0.0)
// 		return (EAST);
// 	else if (ray.x < 0.0 && ray.y < 0.0 && ((int)x % TILE_SIZE > 2))
// 		return (SOUTH);
// 	else if (ray.x < 0.0 && ray.y < 0.0)
// 		return (EAST);
// 	return (NORTH);
// }
