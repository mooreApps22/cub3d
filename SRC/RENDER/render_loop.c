/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:58:10 by smoore            #+#    #+#             */
/*   Updated: 2025/06/03 15:33:23 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	t_rgb_to_hex(t_rgb c)
{
	return (((int)c.r << 16) | ((int)c.g << 8) | (int)c.b);
}

void	paint_ceil_floor(t_cube *data, t_image *buf, t_tex *tx)
{
	int		i;
	int		j;
	char	*address;
	int		offset;
	int		color;

	address = buf->addr;
	j = -1;
	while (++j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			offset = j * data->image.line_len + i * (data->image.bpp / 8);
			color = t_rgb_to_hex(*(tx->ceiling));
			if (j >= HEIGHT / 2)
				color = t_rgb_to_hex(*(tx->floor));
			address[offset] = (color & 0xFF);
			address[offset + 1] = (color >> 8) & 0xFF;
			address[offset + 2] = (color >> 16) & 0xFF;
			address[offset + 3] = (color >> 24) & 0xFF;
			i++;
		}
	}
}

t_image	*get_wall_texture(t_tex *tx, int side)
{
	if (side == NORTH)
		return (tx->north_wall);
	if (side == SOUTH)
		return (tx->south_wall);
	if (side == EAST)
		return (tx->east_wall);
	if (side == WEST)
		return (tx->west_wall);
	return (NULL);
}

void	render_frame(t_cube *data, t_image *buf, t_tex *tx)
{
	t_intersect	*inter;
	int			i;

	inter = ray_casting_main(data);
	if (inter == NULL)
		return ;
	paint_ceil_floor(data, buf, tx);
	i = 0;
	while (i < WIDTH)
	{
		paint_walls(data, &inter[WIDTH - i - 1], i);
		i ++;
	}
	free(inter);
}

int	render_loop(t_cube *data)
{
	data->reset_frame = 0;
	if (data->reset_frame == 0)
	{
		if (data->image.img != NULL)
			mlx_destroy_image(data->mlx_data.mlx_ptr, data->image.img);
		data->image.img = mlx_new_image(data->mlx_data.mlx_ptr, WIDTH, HEIGHT);
		data->image.addr = get_image_addr(&data->image);
		render_frame(data, &data->image, &data->textures);
		mlx_put_image_to_window(data->mlx_data.mlx_ptr,
			data->mlx_data.win_ptr, data->image.img, 0, 0);
		gettimeofday(&data->start, NULL);
	}
	return (0);
}
