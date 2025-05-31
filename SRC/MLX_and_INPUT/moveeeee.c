/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moveeeee.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:00:29 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/31 14:05:29 by mcoskune         ###   ########.fr       */
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

	len = 0;
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

void	validate_movement(t_ply *player, t_tuple dir, t_map *level)
{
	double	check_x;
	double	check_y;

	check_x = (player->pos.x + dir.x * 3) / TILE_SIZE;
	check_y = (player->pos.y + dir.y * 3) / TILE_SIZE;

	// printf("check x value is %d\n", (int)check_x);
	// printf("check y value is %d\n", (int)check_y);
	// printf("LEVEL MAP DATA %d\n", level->data[(int)check_y][(int)check_x]);
	printf("DIRECTION X IS %f\n", dir.x);
	printf("DIRECTION Y IS %f\n", dir.y);


	if ((level->data[(int)check_y][(int)check_x]) != '0')
	{
		printf("Hold your horses cowboy, you can't move there!\n");
		return ;
	}
	(void)level;
	player->pos.x += dir.x;
	player->pos.y += dir.y;
}



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
	// printf("MOVE FORWARD\n");
	// print_player_data(data);
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
	
	
	// printf("MOVE LEFT\n");
	// print_player_data(data);

}

void	move_back(t_cube *data)
{
	t_tuple	dir;

	dir = find_forw_vector(data);
	dir.x *= -1;
	dir.y *= -1;
	validate_movement(&data->player, dir, &data->map);
	
	
	// printf("MOVE BACK\n");
	// print_player_data(data);
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
	
	
	// printf("MOVE RIGHT\n");
	// print_player_data(data);
}
