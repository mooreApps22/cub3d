/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:07:25 by smoore            #+#    #+#             */
/*   Updated: 2025/06/01 17:09:44 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	set_assets_nulls(t_image *asset)
{
	if (!asset)
		return ;
	asset->img = NULL;
	asset->addr = NULL;
	asset->path = NULL;
}

void	set_init_textures_paths_to_null(t_tex *txs)
{
	if (txs->north_wall)
		set_assets_nulls(txs->north_wall);
	if (txs->south_wall)
		set_assets_nulls(txs->south_wall);
	if (txs->east_wall)
		set_assets_nulls(txs->east_wall);
	if (txs->west_wall)
		set_assets_nulls(txs->west_wall);
	if (txs->floor)
	{
		txs->floor->r = -1;
		txs->floor->g = -1;
		txs->floor->b = -1;
	}
	if (txs->ceiling)
	{
		txs->ceiling->r = -1;
		txs->ceiling->g = -1;
		txs->ceiling->b = -1;
	}
}

bool	init_textures(t_tex *txs)
{
	txs->floor = malloc(sizeof(t_rgb));
	if (!txs->floor)
		return (error_msg(0, "floor failed malloc.", NULL));
	txs->ceiling = malloc(sizeof(t_rgb));
	if (!txs->ceiling)
		return (error_msg(0, "Ceiling failed malloc.", NULL));
	txs->north_wall = malloc(sizeof(t_image));
	if (!txs->north_wall)
		return (error_msg(0, "North Wall failed malloc.", NULL));
	txs->south_wall = malloc(sizeof(t_image));
	if (!txs->south_wall)
		return (error_msg(0, "South Wall failed malloc.", NULL));
	txs->east_wall = malloc(sizeof(t_image));
	if (!txs->east_wall)
		return (error_msg(0, "East Wall failed malloc.", NULL));
	txs->west_wall = malloc(sizeof(t_image));
	if (!txs->west_wall)
		return (error_msg(0, "West Wall failed malloc.", NULL));
	set_init_textures_paths_to_null(txs);
	return (true);
}
