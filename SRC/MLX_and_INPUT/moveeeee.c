/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moveeeee.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:00:29 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/22 11:28:38 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

double	tuple_magnitude(t_tuple tuple)
{
	return (sqrt(pow(tuple.x, 2) + pow(tuple.y, 2)));
}

t_tuple	tuple_normalize(t_tuple tuple)
{
	double	len;
	t_tuple	result;

	len = tuple_magnitude(tuple);
	if (len != 0)
	{
		result.x = tuple.x / len;
		result.y = tuple.y / len;
	}
	else
	{
		result.x = 0;
		result.y = 0;
	}
	return (result);
}



static t_tuple	find_forw_vector(t_cube *data)
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
	// if (validate_movement(data, dir) != 0)
	// {
	// 	printf("Hold your horses cowboy, you can't move there!\n");
	// 	return ;
	// }
	data->player.x_pos += dir.x;
	data->player.y_pos += dir.y;
}

void	move_left(t_cube *data)
{
	t_tuple	dir;
	double	temp;

	dir = find_forw_vector(data);
	temp = dir.x;
	dir.x = -dir.y;
	dir.y = temp;
}

void	move_back(t_cube *data)
{
	t_tuple	dir;

	dir = find_forw_vector(data);
	dir.x *= -1;
	dir.y *= -1;
}

void	move_right(t_cube *data)
{
	t_tuple	dir;
	double	temp;

	dir = find_forw_vector(data);
	temp = dir.x;
	dir.x = -dir.y;
	dir.y = -temp;

}
