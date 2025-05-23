/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:56:15 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/22 12:08:44 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_textures(t_cube *data)
{
	data->textures.north_wall = NULL;
	data->textures.south_wall = NULL;
	data->textures.west_wall = NULL;
	data->textures.east_wall = NULL;
	data->textures.floor = NULL;
	data->textures.ceiling = NULL;
}

void	init_mlx(t_cube *data)
{
	data->mlx_data.mlx_ptr = mlx_init(); //we could shorten that
	if (!data->mlx_data.mlx_ptr)
		exit_cleanup("Error - mlx could not be passed to init!\n", NULL, errno);
	data->mlx_data.win_ptr = mlx_new_window(data->mlx_data.mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (!data->mlx_data.mlx_ptr)
		exit_cleanup("Error - window could not be passed to init!\n", NULL, errno);
	data->view.img = mlx_new_window(data->mlx_data.mlx_ptr, WIDTH, HEIGHT, "Shitty Shit Shit");
	data->view.addr = mlx_get_data_addr(data->view.img, &data->view.bpp,
		&data->view.line_len, &data->view.endian);
	data->reset_frame = 1;
	// data->wall = malloc(sizeof(t_image)); 		//Wall is not a pointer
	// if (!data->wall)
	// 	exit_cleanup("Error - wall could not be passed to init!\n", NULL, errno);
	// ft_memset(data->texture, 0, sizeof(t_image));


	// if (data == NULL)
	// 	exit_cleanup("Error - Lux is missing at mlx_init", NULL, -7);
	// data->mlx_ptr = mlx_init();
	// if (data->mlx_ptr == NULL)
	// 	exit_cleanup ("Error - `mlx_init`\n", data, errno);
	// data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH,
	// 		WINDOW_HEIGHT, "minirt");
	// if (data->win_ptr == NULL)
	// 	exit_cleanup ("Error - `mlx_new_win`\n", data, errno);
	// data->image.img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	// if (data->image.img == NULL)
	// 	exit_cleanup ("Error - `mlx_new_image`\n", data, errno);
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
	data->map_data.map = NULL;
	data->textures.north_wall = NULL;
	data->textures.south_wall = NULL;
	data->textures.east_wall = NULL;
	data->textures.west_wall = NULL;
	data->textures.ceiling = NULL;
	data->textures.floor = NULL;
}
