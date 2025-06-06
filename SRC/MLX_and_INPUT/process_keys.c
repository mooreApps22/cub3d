/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:12:51 by smoore            #+#    #+#             */
/*   Updated: 2025/06/06 13:02:06 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	key_press(int key, t_cube *data)
{
	if (key == XK_w)
		data->keys.w = true;
	else if (key == XK_a)
		data->keys.a = true;
	else if (key == XK_s)
		data->keys.s = true;
	else if (key == XK_d)
		data->keys.d = true;
	else if (key == XK_Left)
		data->keys.left = true;
	else if (key == XK_Right)
		data->keys.right = true;
	else if (key == XK_Escape)
		mlx_loop_end(data->mlx_data.mlx_ptr);
	else
		printf("What key is that?!\n");
	return (0);
}

int	key_release(int key, t_cube *data)
{
	(void)key;
	data->keys.w = false;
	data->keys.a = false;
	data->keys.s = false;
	data->keys.d = false;
	data->keys.left = false;
	data->keys.right = false;
	return (0);
}

void	process_keys(t_cube *data)
{
	if (data->keys.w)
		move_forward(data);
	if (data->keys.s)
		move_back(data);
	if (data->keys.d)
		move_right(data);
	if (data->keys.a)
		move_left(data);
	if (data->keys.left)
		turn_left(data);
	if (data->keys.right)
		turn_right(data);
}
