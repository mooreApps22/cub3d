/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_asset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:52:12 by smoore            #+#    #+#             */
/*   Updated: 2025/05/23 17:17:47 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_image	*get_asset(t_tex *assets) // needs a t_ray arg
{
	t_image *asset;	

	//logic from the t_ray selects the right asset
	asset = assets->east_wall; // <- Just a place holder for now
	return (asset);
}
