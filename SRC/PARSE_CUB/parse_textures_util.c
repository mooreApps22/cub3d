/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:18:20 by smoore            #+#    #+#             */
/*   Updated: 2025/05/20 12:42:27 by mcoskune         ###   ########.fr       */
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
			tex->west_wall != NULL && tex->east_wall != NULL)
		return (true);
	return (false);
}
