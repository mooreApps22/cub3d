/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turrrrrn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:02:39 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/22 09:23:06 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


static void normalize_angle_deg(double *angle)
{
	*angle = fmod(*angle + M_PI / 2, M_PI);
	if (*angle < 0)
		*angle += M_PI;
	*angle = *angle - (M_PI / 2);
}

void	turn_left(t_cube *data)
{
	double	rad_turn_rate;

	rad_turn_rate = deg_to_rad(TURN_RATE);
	data->player.alpha += rad_turn_rate;
	normalize_angle_deg(&data->player.alpha);
}

void	turn_right(t_cube *data)
{
	double	rad_turn_rate;

	rad_turn_rate = deg_to_rad(TURN_RATE);
	data->player.alpha -= rad_turn_rate;
	normalize_angle_deg(&data->player.alpha);
}
