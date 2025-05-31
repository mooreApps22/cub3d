/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:40:27 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/30 17:10:25 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	mouse_input(int x, int y, t_cube *data)
{
	if (x < 0 || y < 0)
		turn_left(data);
	// else if (x > 0)
	// 	turn_right(data);

	// printf("Mouse moved to (%d, %d)\n", x, y);
	return (0);
}

int	handle_keys(int keysys, t_cube *data)
{
	if (keysys == XK_Escape)
		mlx_loop_end(data->mlx_data.mlx_ptr);
	else if (keysys == XK_w)
		move_forward(data);
	else if (keysys == XK_a)
		move_left(data);
	else if (keysys == XK_s)
		move_back(data);
	else if (keysys == XK_d)
		move_right(data);
	else if (keysys == XK_Left)
		turn_left(data);
	else if (keysys == XK_Right)
		turn_right(data);
	else
		write(1, "WTF IS THIS BUTTON YOU DONKEY?!\n", 33);
	return (0);
}

int	handle_x_button(t_cube *data)
{
	mlx_loop_end(data->mlx_data.mlx_ptr);
	return (0);
}
