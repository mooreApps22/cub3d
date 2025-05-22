/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:56:15 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/22 11:43:46 by mcoskune         ###   ########.fr       */
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

// void	init_mlx(t_cube *lux)
// {
// 	// if (lux == NULL)
// 	// 	exit_cleanup("Error - Lux is missing at mlx_init", NULL, -7);
// 	// lux->mlx_ptr = mlx_init();
// 	// if (lux->mlx_ptr == NULL)
// 	// 	exit_cleanup ("Error - `mlx_init`\n", lux, errno);
// 	// lux->win_ptr = mlx_new_window(lux->mlx_ptr, WINDOW_WIDTH,
// 	// 		WINDOW_HEIGHT, "minirt");
// 	// if (lux->win_ptr == NULL)
// 	// 	exit_cleanup ("Error - `mlx_new_win`\n", lux, errno);
// 	// lux->image.img = mlx_new_image(lux->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
// 	// if (lux->image.img == NULL)
// 	// 	exit_cleanup ("Error - `mlx_new_image`\n", lux, errno);
// }

void	initialize(t_cube *data)
{
	// lux->mlx_ptr = NULL;
	// lux->win_ptr = NULL;
	// lux->image.img = NULL;
	// lux->image.addr = NULL;
	// lux->image.bpp = -1;
	// lux->image.line_len = -1;
	// lux->image.endian = -1;
	// lux->p_light = NULL;
	// lux->a_light = NULL;
	// lux->camera = NULL;
	// lux->objects = NULL;
	// lux->file_fd = -1;
}