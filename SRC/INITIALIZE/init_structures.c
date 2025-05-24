/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:56:15 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/24 17:46:07 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_mlx(t_cube *data)
{
	data->mlx_data.mlx_ptr = mlx_init(); //we could shorten that
	if (!data->mlx_data.mlx_ptr)
		exit_cleanup("Error - mlx could not be passed to init!\n", NULL, errno);
	data->mlx_data.win_ptr = mlx_new_window(data->mlx_data.mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (!data->mlx_data.win_ptr)
		exit_cleanup("Error - window could not be passed to init!\n", NULL, errno);
	data->image.img = mlx_new_image(data->mlx_data.mlx_ptr, WIDTH, HEIGHT);
	if (data->image.img == NULL)
		exit_cleanup ("Error - `mlx_new_image`\n", data, errno);
	data->image.addr = get_image_addr(&data->image);
	data->reset_frame = 1;
}

void	clean_initialize(t_cube *data)
{
	data->mlx_data.mlx_ptr = NULL;
	data->mlx_data.win_ptr = NULL;
	data->image.img = NULL;
	data->image.addr = NULL;
	data->image.bpp = -1;
	data->image.line_len = -1;
	data->image.endian = -1;
	data->map_data.map = ft_str_arr_init();
	data->textures.north_wall = NULL;
	data->textures.south_wall = NULL;
	data->textures.east_wall = NULL;
	data->textures.west_wall = NULL;
	data->textures.ceiling = NULL;
	data->textures.floor = NULL;
}
