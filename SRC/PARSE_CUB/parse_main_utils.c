/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:13:43 by smoore            #+#    #+#             */
/*   Updated: 2025/06/01 12:39:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	validate_xpm_extensions(t_tex *txs)
{
	if (!txs || !txs->north_wall || !txs->south_wall ||
		!txs->east_wall || !txs->west_wall)
		return (error_msg(0, "Missing texture structures", NULL));
	if (!txs)
		return (error_msg(0, "failed to pass t_tex of .xpm validation", NULL));
	if (!validate_xpm_extension(txs->north_wall->path))
		return (error_msg(0, "failed to validate north wall xpm ext", NULL));
	if (!validate_xpm_extension(txs->south_wall->path))
		return (error_msg(0, "failed to validate south wall xpm ext", NULL));
	if (!validate_xpm_extension(txs->east_wall->path))
		return (error_msg(0, "failed to validate east wall xpm ext", NULL));
	if (!validate_xpm_extension(txs->west_wall->path))
		return (error_msg(0, "failed to validate west wall xpm ext", NULL));
	return (true);
}

bool	validate_map_dimensions(t_map *map)
{
	int current_width;

	if (!map)
		ft_putstr_fd("Error - failed to pass map.\n", 2);
	current_width = 0;
	while (map->data[map->height])
	{
		current_width = ft_strlen(map->data[map->height]);
		if (current_width >  map->width)
			map->width = current_width;
		map->height++;
	}
	return (true);
}
