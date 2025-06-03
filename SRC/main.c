/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:29:19 by mcoskune          #+#    #+#             */
/*   Updated: 2025/06/03 13:54:08 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	game_start(t_cube *data)
{
	mlx_loop_hook(data->mlx_data.mlx_ptr, render_loop, data);
	mlx_hook(data->mlx_data.win_ptr, 17, 0, handle_x_button, data);
	mlx_hook(data->mlx_data.win_ptr, 2, 1L << 0, handle_keys, data);
	mlx_hook(data->mlx_data.win_ptr, 6, 1L << 6, mouse_input, data);
	mlx_loop(data->mlx_data.mlx_ptr);
	return (0);
}

int	main(int ac, char **av)
{
	t_cube	data;

	validate_input(ac, av);
	clean_initialize(&data);
	init_mlx(&data);
	if (!parse_main(&data, av[1]))
		exit_cleanup("Error - Parsing failed\n", &data, errno);
	game_start(&data);
	printf("REACHED END OF MAIN\n");
	exit_cleanup("Thanks for playing our game, \
		we hope you hated it!\n", &data, 0);
	return (0);
}
