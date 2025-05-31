/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:58:10 by smoore            #+#    #+#             */
/*   Updated: 2025/05/31 19:32:39 by smoore           ###   ########.fr       */
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

int	get_wall_color(t_intersect *inter)
{
	t_rgb	north; 
	t_rgb	east;
	t_rgb	south;
	t_rgb	west;
	t_rgb	def;

	def.r = 255;
	def.g = 255;
	def.g = 255;
	north.r = 255;
	north.g = 0;
	north.b = 0;
	east.r = 0;
	east.g = 0;
	east.b = 255;
	south.r = 0;
	south.g = 255;
	south.b = 0;
	west.r = 255;
	west.g = 255;
	west.b = 0;
	if (inter->side == NORTH)
		return (t_rgb_to_hex(north));
	else if (inter->side == EAST)
		return (t_rgb_to_hex(east));
	else if (inter->side == SOUTH)
		return (t_rgb_to_hex(south));
	else if (inter->side == WEST)
		return (t_rgb_to_hex(west));
	return (t_rgb_to_hex(def));
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

void	paint_walls(t_cube *data, t_image *buf, t_tex *tx, t_intersect *inter, int i)
{
	int		j;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		wall_h;
	t_image	*tex;
	char	*address;

	(void)data;
	address = buf->addr;
	tex = get_wall_texture(tx, inter->side);
	if (!tex || !tex->addr)	
		return ;
	wall_h = wall_height(inter);
	if (inter->side == EAST || inter->side == WEST)
		tex_x = (int)inter->y % TILE_SIZE;
	else
		tex_y = (int)inter->x % TILE_SIZE;
	tex_x = tex_x * tex->width / TILE_SIZE;
	step = (double)tex->height / wall_h;
	tex_pos = 0.0;
	j = HEIGHT / 2 - wall_h / 2;
	if (j < 0)
	{
		tex_pos = -j * step;
		j = 0;
	}
	while (j < HEIGHT / 2 + wall_h / 2 && j < HEIGHT)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;

		int	tex_offset = tex_y * tex->line_len + tex_x * (tex->bpp / 8);
		int	screen_offset = j * buf->line_len + i * (buf->bpp / 8);
		for (int k = 0; k < 4; ++k)
			address[screen_offset + k] = tex->addr[tex_offset + k];
		j++;
	}
}



void	render_frame(t_cube *data, t_image *buf, t_tex *tx)
{
	t_intersect	*inter;
	int			i; //for x dir

	inter = ray_casting_main(data);
	if (inter == NULL)
		return ;
	paint_ceil_floor(data, buf, tx);
	i = 0;
	while (i < WIDTH)
	{
		paint_walls(data, buf, tx, &inter[WIDTH - i - 1], i);
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
		data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bpp, &data->image.line_len, &data->image.endian);
		render_frame(data, &data->image, &data->textures);
		mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.win_ptr, data->image.img, 0, 0);
		gettimeofday(&data->start, NULL);
		// printf("Player Location - X: %f\n", data->player.pos.x);
		// printf("Player Location - Y: %f\n\n", data->player.pos.y);
	}
	// data->reset_frame = render_timer(data);
	return (0);
}

