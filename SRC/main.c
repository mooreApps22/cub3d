/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:29:19 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/30 21:39:48 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	game_start(t_cube *data)
{
	mlx_loop_hook(data->mlx_data.mlx_ptr, render_loop, data);
	mlx_hook(data->mlx_data.win_ptr, 17, 0, handle_x_button, data);
	mlx_hook(data->mlx_data.win_ptr, 2, 1L<<0, handle_keys, data);
	mlx_hook(data->mlx_data.win_ptr, 6, 1L << 6, mouse_input, data);
	mlx_loop(data->mlx_data.mlx_ptr);
	return (0);
}

void init_temp_hard_values(t_cube *data)
{
	data->player.alpha = 0;
	data->player.pos.x = TILE_SIZE * 1 + TILE_SIZE / 2; // player at (1,4)
	data->player.pos.y = TILE_SIZE * 4 + TILE_SIZE / 2;

	data->map.width = 4;
	data->map.height = 6;
	free_dptr((void **)data->map.data);
	data->map.data = safe_malloc(sizeof(char *), 8);
	data->map.data[0] = ft_strdup("1111");
	data->map.data[1] = ft_strdup("1001");
	data->map.data[2] = ft_strdup("1011");
	data->map.data[3] = ft_strdup("1001");
	data->map.data[4] = ft_strdup("1001");
	data->map.data[5] = ft_strdup("1001");
	data->map.data[6] = ft_strdup("1111");
	data->map.data[7] = NULL;
}

int	main(int ac, char **av)
{
	t_cube	data;

	validate_input(ac, av);
	clean_initialize(&data);
	if (!parse_main(&data, av[1]))
		exit_cleanup("Error - Parsing failed\n", &data, errno);

	init_temp_hard_values(&data);
	init_mlx(&data);
	game_start(&data);

	
	printf("REACHED END OF MAIN\n");
	exit_cleanup("Thanks for playing our game, we hope you hated it!\n", &data, 0);
	return (0);
}





// // ************************************************************************** //
// //                             MANUAL DATA INIT                               //
// // ************************************************************************** //
// 	
// // ************************************************************************** //
// //                              END DATA INIT                                 //
// // ************************************************************************** //
// 	gettimeofday(&data.start, NULL); //Need to get the start of game/frame time

// 	free(data.map.data[0]);
// 	free(data.map.data[1]);
// 	free(data.map.data[2]);
// 	free(data.map.data[3]);
// 	free(data.map.data[4]);
// 	free(data.map.data[5]);
// 	free(data.map.data[6]);
// 	free(data.map.data);
// 	data.map.data = NULL;


// 	return (0);
// }
