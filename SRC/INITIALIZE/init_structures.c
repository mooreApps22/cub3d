/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:56:15 by mcoskune          #+#    #+#             */
/*   Updated: 2025/06/03 15:45:26 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_camera(t_camera *cam)
{
	cam->fov = M_PI / 3;
	cam->turn_size = M_PI / (WIDTH * cam->fov);
	cam->pp_size = WIDTH * HEIGHT;
	cam->pp_x = WIDTH / 2;
	cam->pp_y = HEIGHT / 2;
	cam->dist_to_pp = cam->pp_x / tan(cam->fov / 2);
	cam->delta_fov = cam->fov / WIDTH;
}

void	init_mlx(t_cube *data)
{
	data->mlx_data.mlx_ptr = mlx_init();
	printf("init file mlx ptr: %p\n", data->mlx_data.mlx_ptr);
	if (!data->mlx_data.mlx_ptr)
		exit_cleanup("Error - mlx could not be passed to init!\n", NULL, errno);
	data->mlx_data.win_ptr = mlx_new_window(data->mlx_data.mlx_ptr,
			WIDTH, HEIGHT, "cub3d");
	if (!data->mlx_data.win_ptr)
		exit_cleanup("Error - window could not be passed to init!\n",
			NULL, errno);
	data->image.img = mlx_new_image(data->mlx_data.mlx_ptr, WIDTH, HEIGHT);
	if (data->image.img == NULL)
		exit_cleanup ("Error - `mlx_new_image`\n", data, errno);
	data->image.addr = get_image_addr(&data->image);
	if (!data->image.addr)
		exit_cleanup ("Error - failed to init image address\n", data, errno);
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
	data->map.data = NULL;
	data->map.height = 0;
	data->map.width = 0;
	data->map.map_line_start = 0;
	data->textures.north_wall = NULL;
	data->textures.south_wall = NULL;
	data->textures.east_wall = NULL;
	data->textures.west_wall = NULL;
	data->textures.ceiling = NULL;
	data->textures.floor = NULL;
	data->player.alpha = -1.0;
	init_camera(&data->cam);
}
