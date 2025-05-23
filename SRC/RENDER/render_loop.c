/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:58:10 by smoore            #+#    #+#             */
/*   Updated: 2025/05/23 17:15:32 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	iterate_down_image_buffer(t_image *buf, t_image *asset);
void	iterate_across_image_buffer(t_image *buf, t_tex *assets);
void	render_frame(t_cube *data, t_image *buf, t_tex *tx);

void	iterate_down_image_buffer(t_image *buf, t_image *asset)
{
	buf->y = 0;
	while (buf->y < HEIGHT)
	{
		if (buf->y >= asset->y && buf->y <= asset->height + asset->y)
		{
			asset->color = get_color(asset, asset->x, asset->y);
			blit_pixel_color(buf, buf->x, buf->y, asset->color); // skip or repeat option 
		}
		buf->y++;
	}
}


void	iterate_across_image_buffer(t_image *buf, t_tex *assets) // needs a t_ray arg 
{
	t_image	*asset;

	buf->x = 0;
	while (buf->x < WIDTH)
	{
		//pick asset
		asset = get_asset(assets); // needs a t_ray arg
		if (buf->x >= asset->x && buf->x <= asset->width + asset->x)
			iterate_down_image_buffer(buf, assets->east_wall); // 
		buf->x++;
	}
}

void	render_frame(t_cube *data, t_image *buf, t_tex *tx)
{
	iterate_across_image_buffer(buf, tx);
	mlx_put_image_to_window(data->mlx_data.mlx_ptr, data->mlx_data.win_ptr,
		buf->img, 0, 0);
}

int	render_loop(t_cube *data)
{
	if (data->reset_frame)
	{
		render_frame(data, &data->image, &data->textures);
		data->reset_frame = 0;
	}
	return (0);
}
