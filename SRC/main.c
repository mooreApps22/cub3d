/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:29:19 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/29 15:58:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
int	game_start(t_cube *data)
{
	mlx_loop_hook(data->mlx_data.mlx_ptr, render_loop, data);
	mlx_hook(data->mlx_data.win_ptr, 17, 0, handle_x_button, data);
	mlx_key_hook(data->mlx_data.win_ptr, handle_keys, data);
	mlx_loop(data->mlx_data.mlx_ptr);
	return (0);
}


int	main(int ac, char **av)
{
	t_cube	data;
	
	validate_input(ac, av);
	clean_initialize(&data);
	if (!parse_main(&data, av[1]))
		exit_cleanup("Error - Parsing failed\n", &data, errno);
//	init_mlx(&data);
//	data.player.alpha = 0; // PLAYER DIRECTION NOT INITIALIZED!!! 0 is east
//	gettimeofday(&data.start, NULL); //Need to get the start of game/frame time
	
	// game_start(&data);

//	ray_casting_main(&data);

	printf("REACHED END OF MAIN\n");
	exit_cleanup("Thanks for playing our game, we hope you hated it!\n", &data, 0);
	return (0);
}
