/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:18:20 by smoore            #+#    #+#             */
/*   Updated: 2025/05/22 19:31:43 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
		if (all_found(data->tex))
			break ;
*/

bool	all_textures_found(t_tex *tex)
{
	if (tex->north_wall != NULL && tex->south_wall != NULL && \
			tex->west_wall != NULL && tex->east_wall != NULL && \
				tex->floor != NULL && tex->ceiling != NULL)
		return (true);
	return (false);
}
