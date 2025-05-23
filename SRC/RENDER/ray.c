/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:48:12 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/23 12:53:44 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


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