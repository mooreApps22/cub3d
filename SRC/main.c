/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:29:19 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/20 19:39:09 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	game_start(t_cube *data)
{
	mlx_loop_hook(data->mlx_data.mlx_ptr, create_image, data);
	mlx_hook(data->mlx_data.win_ptr, 17, 0, handle_x_button, data);
	mlx_key_hook(data->mlx_data.win_ptr, handle_keys, data);
	mlx_loop(data->mlx_data.mlx_ptr);
	return (0);
}


int	main(int ac, char **av)
{
	t_cube	data;
	
	validate_input(ac, av);
	parse_main(&data, av[1]);
	// mlx_look_hook(data.mlx_data.mlx_ptr, render_loop, &data);
	// mlx_loop(data.mlx_data.mlx_ptr);
	// initialize(&data);
	// game_start(&data);

	printf("REACHED END OF MAIN\n");
	return (0);
}



