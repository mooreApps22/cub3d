/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turrrrrn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:02:39 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/30 21:48:48 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


void normalize_deg(double *angle)
{
	if (*angle >= 0 && *angle < 2 * M_PI)
		return ;
	while (*angle >= 2 * M_PI)
		(*angle) -= M_PI;
	while (*angle < 0)
		(*angle) += 2 * M_PI;
	// *angle = fmod(*angle + M_PI / 2, M_PI);
	// if (*angle < 0)
	// 	*angle += M_PI;
	// *angle = *angle - (M_PI / 2);
}

void	turn_left(t_cube *data)
{
	double	rad_turn_rate;

	rad_turn_rate = deg_to_rad(TURN_RATE);
	data->player.alpha += rad_turn_rate;
	normalize_deg(&data->player.alpha);
	
	
	printf("TURN LEFT\n");
	print_player_data(data);

}

void	turn_right(t_cube *data)
{
	double	rad_turn_rate;

	rad_turn_rate = M_PI / 180;
	data->player.alpha -= rad_turn_rate;
	normalize_deg(&data->player.alpha);
	
	
	printf("TURN RIGHT\n");
	print_player_data(data);

}
