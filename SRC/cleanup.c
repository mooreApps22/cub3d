/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:37:04 by mcoskune          #+#    #+#             */
/*   Updated: 2025/06/01 16:49:55 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	clean_mlx_data(t_cube *data)
{
	if (data->mlx_data.win_ptr)
	{
		mlx_destroy_window(data->mlx_data.mlx_ptr, data->mlx_data.win_ptr);
		data->mlx_data.win_ptr = NULL;
	}
	if (data->image.img)
	{
		mlx_destroy_image(data->mlx_data.mlx_ptr, data->image.img);
		data->image.img = NULL;
	}
	if (data->mlx_data.mlx_ptr)
	{
		mlx_destroy_display(data->mlx_data.mlx_ptr);
		free(data->mlx_data.mlx_ptr);
		data->mlx_data.mlx_ptr = NULL;
	}
	data->image.addr = NULL;
}

static void	clean_texture_image(t_image *img, void *mlx_ptr)
{
	if (!img)
		return ;
	if (img->img && mlx_ptr)
	{
		mlx_destroy_image(mlx_ptr, img->img);
		img->img = NULL;
	}
	if (img->path)
	{
		free(img->path);
		img->path = NULL;
	}
	free(img);
}

static void	clean_texture_data(t_cube *data)
{
	if (data->textures.north_wall)
		clean_texture_image(data->textures.north_wall, data->mlx_data.mlx_ptr);
	if (data->textures.south_wall)
		clean_texture_image(data->textures.south_wall, data->mlx_data.mlx_ptr);
	if (data->textures.west_wall)
		clean_texture_image(data->textures.west_wall, data->mlx_data.mlx_ptr);
	if (data->textures.east_wall)
		clean_texture_image(data->textures.east_wall, data->mlx_data.mlx_ptr);
	if (data->textures.floor)
	{
		free(data->textures.floor);
		data->textures.floor = NULL;
	}
	if (data->textures.ceiling)
	{
		free(data->textures.ceiling);
		data->textures.ceiling = NULL;
	}
}

void	exit_cleanup(char *msg, t_cube *data, int exit_code)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	clean_texture_data(data);
	clean_mlx_data(data);
	if (data->map.data)
		free_dptr((void **)data->map.data);
	exit(exit_code);
}
