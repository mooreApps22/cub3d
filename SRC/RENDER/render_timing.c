/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_timing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:51:41 by mcoskune          #+#    #+#             */
/*   Updated: 2025/06/03 14:20:19 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @brief This function is used to limit FPS of rendering.
 */

int	render_timer(t_cube *data)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	if (current.tv_usec - data->start.tv_usec < 1000000 / 30)
	{
		printf("Not enough time passed\n");
		return (1);
	}
	return (0);
}
