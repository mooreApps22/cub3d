/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moveeeee.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:00:29 by mcoskune          #+#    #+#             */
/*   Updated: 2025/06/01 16:59:28 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_tuple	find_forw_vector(t_cube *data)
{
	t_tuple	forward;

	forward.x = cos(data->player.alpha);
	forward.y = sin(data->player.alpha);
	forward = tuple_normalize(forward);
	return (forward);
}

void	move_forward(t_cube *data)
{
	t_tuple	dir;

	dir = find_forw_vector(data);
	validate_movement(&data->player, dir, &data->map);
}

void	move_left(t_cube *data)
{
	t_tuple	dir;
	double	temp;

	dir = find_forw_vector(data);
	temp = dir.x;
	dir.x = dir.y;
	dir.y = -temp;
	validate_movement(&data->player, dir, &data->map);
}

void	move_back(t_cube *data)
{
	t_tuple	dir;

	dir = find_forw_vector(data);
	dir.x *= -1;
	dir.y *= -1;
	validate_movement(&data->player, dir, &data->map);
}

void	move_right(t_cube *data)
{
	t_tuple	dir;
	double	temp;

	dir = find_forw_vector(data);
	temp = dir.x;
	dir.x = -dir.y;
	dir.y = temp;
	validate_movement(&data->player, dir, &data->map);
}
