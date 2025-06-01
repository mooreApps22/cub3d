/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:57:38 by smoore            #+#    #+#             */
/*   Updated: 2025/06/01 16:58:10 by smoore           ###   ########.fr       */
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
