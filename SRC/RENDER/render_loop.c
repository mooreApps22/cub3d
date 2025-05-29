/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:58:10 by smoore            #+#    #+#             */
/*   Updated: 2025/05/29 16:41:54 by mcoskune         ###   ########.fr       */
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

void	paint_walls(t_cube *data, t_image *buf, t_tex *tx, t_intersect *inter, int i)
{
	int		j;
	char	*address;
	int		offset;
	int		color;
	int		wall_h;

	address = buf->addr;
	t_rgb	north; t_rgb	east; t_rgb	south; t_rgb	west;
	north.r = 255; north.g = 0; north.b = 0;
	east.r = 0; east.g = 0; east.b = 255;
	south.r = 0; south.g = 255; south.b = 0;
	west.r = 255; west.g = 255; west.b = 0;

	(void)tx;
	t_rgb	def;
	def.r = 255; def.g = 255; def.g = 255;
	color = t_rgb_to_hex(def);
	if (inter->side == NORTH)
		color = t_rgb_to_hex(north);
	else if (inter->side == EAST)
		color = t_rgb_to_hex(east);
	else if (inter->side == SOUTH)
		color = t_rgb_to_hex(south);
	else if (inter->side == WEST)
		color = t_rgb_to_hex(west);
	wall_h = wall_height(inter);
	printf("Wall height is %d\n", wall_h);
	j = HEIGHT / 2 - wall_h / 2;
	while (j < HEIGHT / 2 + wall_h / 2)
	{
			offset = j * data->image.line_len + i * (data->image.bpp / 8);
			address[offset] = (color & 0xFF);
			address[offset + 1] = (color >> 8) & 0xFF;
			address[offset + 2] = (color >> 16) & 0xFF;
			address[offset + 3] = (color >> 24) & 0xFF;
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
	if (data->reset_frame == 0)
	{
		if (data->image.img != NULL)
			mlx_destroy_image(data->mlx_data.mlx_ptr, data->image.img);
		data->image.img = mlx_new_image(data->mlx_data.mlx_ptr, WIDTH, HEIGHT);
		data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bpp, &data->image.line_len, &data->image.endian);
		render_frame(data, &data->image, &data->textures);
		mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.win_ptr, data->image.img, 0, 0);
		gettimeofday(&data->start, NULL);
	}
	data->reset_frame = render_timer(data);
	return (0);
}

// void	iterate_down_image_buffer(t_image *buf, t_image *asset);
// void	iterate_across_image_buffer(t_image *buf, t_tex *assets);
// void	render_frame(t_cube *data, t_image *buf, t_tex *tx);

// void	iterate_down_image_buffer(t_image *buf, t_image *asset)
// {
// 	buf->y = 0;
// 	while (buf->y < HEIGHT)
// 	{
// 		if (buf->y >= asset->y && buf->y <= asset->height + asset->y)
// 		{
// 			asset->color = 0; //get_color(asset, asset->x, asset->y);
// 			blit_pixel_color(buf, buf->x, buf->y, asset->color); // skip or repeat option 
// 		}
// 		buf->y++;
// 	}
// }


// void	iterate_across_image_buffer(t_image *buf, t_tex *assets) // needs a t_ray arg 
// {
// 	t_image	*asset;

// 	buf->x = 0;
// 	while (buf->x < WIDTH)
// 	{
// 		//pick asset
// 		asset = get_asset(assets); // needs a t_ray arg
// 		if (buf->x >= asset->x && buf->x <= asset->width + asset->x)
// 			iterate_down_image_buffer(buf, assets->east_wall); // 
// 		buf->x++;
// 	}
// }

// void	render_frame(t_cube *data, t_image *buf, t_tex *tx)
// {
// 	iterate_across_image_buffer(buf, tx);
// 	mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.win_ptr,
// 		buf->img, 0, 0);
// }

// int	render_loop(t_cube *data)
// {
// 	if (data->reset_frame == 0)
// 	{
// 		render_frame(data, &data->image, &data->textures);
// 		gettimeofday(&data->start, NULL);
// 	}
// 	data->reset_frame = render_timer(data);
// 	return (0);
// }





// old stuff

// t_tuple	ray_create(double x, double y)
// {
// 	t_tuple ray;

// 	ray.x = x;
// 	ray.y = y;
// }


// static double	tuple_dot(t_tuple tup1, t_tuple tup2)
// {
// 	return (tup1.x * tup2.x + tup1.y* tup2.y);
// }

// static t_dir	find_direction(t_cube *data, double x, double y, t_tuple ray)
// {
// 	if (ray.x == 0.0 && ray.y > 0.0)
// 		return (NORTH);
// 	else if (ray.x == 0.0 && ray.y < 0.0)
// 		return (SOUTH);
// 	else if (ray.x > 0.0 && ray.y == 0.0)
// 		return (WEST);
// 	else if (ray.x < 0.0 && ray.y == 0.0)
// 		return (EAST);
// 	else if (ray.x > 0.0 && ray.y > 0.0 && ((int)x % TILE_SIZE > 2))
// 		return (NORTH);
// 	else if (ray.x > 0.0 && ray.y > 0.0)
// 		return (WEST);
// 	else if (ray.x > 0.0 && ray.y < 0.0 && ((int)x % TILE_SIZE > 2))
// 		return (SOUTH);
// 	else if (ray.x > 0.0 && ray.y < 0.0)
// 		return (WEST);
// 	else if (ray.x < 0.0 && ray.y > 0.0 && ((int)x % TILE_SIZE > 2))
// 		return (NORTH);
// 	else if (ray.x < 0.0 && ray.y > 0.0)
// 		return (EAST);
// 	else if (ray.x < 0.0 && ray.y < 0.0 && ((int)x % TILE_SIZE > 2))
// 		return (SOUTH);
// 	else if (ray.x < 0.0 && ray.y < 0.0)
// 		return (EAST);
// 	return (NORTH);
// }