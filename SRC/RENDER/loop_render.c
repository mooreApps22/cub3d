/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:58:10 by smoore            #+#    #+#             */
/*   Updated: 2025/05/23 13:51:31 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	render(t_cube *data, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		*(unsigned int *)(data->addr
			+ y * data->line_len + x * (data->bpp / 8)) = color;
}

void	draw_wall_strip(t_cube *data, t_image *wall, int x, int scaled_height)
{
	int	tex_x;
	int	y0;
	int	y1;

	if (x < 0 ||| x >= WIDTH)
		return ;
	tex_x = (x * wall->width) / WIDTH;
	y0 = (HEIGHT - scaled_height) / 2;
	y1 = y0 + scaled_height;
	// well need to be extracted
	for (int y = 0; y < HEIGHT; y++)
	{
		if (y < y0 || y > y1)
			render(data, x, y, BLACK);
		else
		{
			float pixel_repeater = (float)wall->height / scaled_height;
			int tex_y = (y - y0) * pixel_repeater;
			unsigned int color = *(unsigned int *)(wall->addr,
				tex_y * wall->line_len + tex_x * (texture->bpp / 8));
			render(data, x, y, color);
		}
	}
}

int	reset_frame(t_cube *data, t_image *wall, t_mlx *mlx)
{
	int	x;
	int	scaled_height;

	if (!wall->img)
	{
		wall->img = mlx_xpm_file_to_image(mlx->mlx_ptr, "TEXTURES/east.xpm",
			&wall->width, &wall->height);
		if (!wall->img)
		{
			// exit clean_up goes here	
		}
		wall->addr = mlx_get_data_addr(wall->img, &wall->bpp, &wall->line_len, &wall->en);

	}
	x = 0;
	while (x < WIDTH)
	{
		scaled_height = 10 + x * (HEIGHT - 10) / WIDTH;
		draw_wall_strip(data, wall, x, scaled_height);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx_win_ptr, data->view->img, 0, 0);
	return (0);
}

int	render_loop(t_cube *data)
{
	if (data->reset_frame)
	{
		reset_frame(data, data->wall, data->mlx_data);
		data->reset_frame = 0; 
	}
	return (0);
}
