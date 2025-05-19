/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:53:45 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/19 15:55:51 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	validate_input(int ac, char **av)
{
	if (ac != 2)
		exit_cleanup("Error - Wrong AC\n", NULL, -1);
	if (ft_strlen(av[1]) <= 3)
		exit_cleanup("Error - File name too short!\n", NULL, -2);
	if (check_extension(av[1], ".cub") != 0)
		exit_cleanup("Error - Wrong file extension!\n", NULL, -3);
	if (check_access(av[1], 0) != 0)
		exit_cleanup("Error - File Permissions!\n", NULL, -4);
}
