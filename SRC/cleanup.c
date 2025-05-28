/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:37:04 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/27 19:24:57 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
/*
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

*/

static void	clean_texture_image(t_image *img)
{
	if (img)
	{
		if (img->path)
			free(img->path);
		free(img);
	}
}

static void	clean_texture_data(t_cube *data)
{
	clean_texture_image(data->textures.north_wall);
	clean_texture_image(data->textures.south_wall);
	clean_texture_image(data->textures.west_wall);
	clean_texture_image(data->textures.east_wall);
	if (data->textures.floor)
		free(data->textures.floor);
	if (data->textures.ceiling)
		free(data->textures.ceiling);
//	free(data->texture.floor);
//	data->textures.floor = NULL;	
//	free(data->texture.ceiling);
//	data->textures.ceiling = NULL;	
}

void	exit_cleanup(char *msg, t_cube *data, int exit_code)
{
	if (msg)
		ft_putstr_fd(msg, 2);
//	clean_mlx_data(data);
	if (data->map.data)
		ft_str_arr_free(&data->map.data);
	clean_texture_data(data);

	// clean_player_data(data); there is nothing malloced at player atm

	exit(exit_code);
}
