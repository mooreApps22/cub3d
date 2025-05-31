/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:12:02 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/30 17:19:01 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"



void	print_player_data(t_cube *data)
{
	printf("Player X Grid Position: %d\n", (int)(data->player.pos.x / TILE_SIZE));
	printf("Player Y Grid Position: %d\n\n", (int)(data->player.pos.y / TILE_SIZE));


	printf("Player X Position: %f\n", data->player.pos.x);
	printf("Player Y Position: %f\n\n", data->player.pos.y);

	printf("Player Orientation: %f\n\n", data->player.alpha);
}