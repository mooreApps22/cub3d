/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_timing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:51:41 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/28 12:55:39 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @brief This function is used to limit FPS of rendering.
 */
int	render_timer(t_cube *data)
{
	struct timeval	current;
	// time_t			elapsed_usec;

	gettimeofday(&current, NULL);
	if (current.tv_usec - data->start.tv_usec < 1000000 / 30)
	{
		// printf("Not enough time passed\n");
		return (1);
	}
	// gettimeofday(&start, NULL);


	// elapsed_usec = (current.tv_sec - data->start.tv_sec) * 1000000L + (current.tv_usec - data->start.tv_usec);
	// printf("Elapsed time: %.3f seconds\n", elapsed_usec / 1000000.0);
	return (0);
}
