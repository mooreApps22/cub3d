/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_first_six_lines.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:13:43 by smoore            #+#    #+#             */
/*   Updated: 2025/05/29 15:57:33 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	set_init_textures_paths_to_null(t_tex *txs)
{
	txs->north_wall->path = NULL;
	txs->south_wall->path = NULL;
	txs->east_wall->path = NULL;
	txs->west_wall->path = NULL;
	txs->floor->r = -1;
	txs->floor->g = -1;
	txs->floor->b= -1;
	txs->ceiling->r = -1;
	txs->ceiling->g = -1;
	txs->ceiling->b= -1;
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

bool	match_texture_path(char *line, t_tex *txs)
{
	bool	found;

	found = false;
	if (assign_texture_path(line, "NO ", &txs->north_wall->path))
		found = true;
	if (assign_texture_path(line, "SO ", &txs->south_wall->path))
		found = true;
	if (assign_texture_path(line, "EA ", &txs->east_wall->path))
		found = true;
	if (assign_texture_path(line, "WE ", &txs->west_wall->path))
		found = true;
	if (assign_color_values(line, "F ", txs->floor))
		found = true;
	if (assign_color_values(line, "C ", txs->ceiling))
		found = true;
	return (found);
}

bool	validate_all_textures_are_found(t_tex *txs)
{
	return (txs->north_wall->path &&
		txs->south_wall->path && 
		txs->east_wall->path &&
		txs->west_wall->path && 
		txs->ceiling->r >= 0 &&
		txs->ceiling->g >= 0 &&
		txs->ceiling->b >= 0 &&
		txs->floor->r >= 0 &&
		txs->floor->g >= 0 &&
		txs->floor->b >= 0);
}

bool	validate_first_six_lines(char **map, t_tex *txs, int *map_line_start)
{
	if (!init_textures(txs))
		return (error_msg(0, "t_tex failed malloc.", NULL));
	while (true)
	{
		if (!(*map))
		{
			if (validate_all_textures_are_found(txs))
				break ;
			return (error_msg(0, "Failed to match texture paths.", NULL)); //
		}
		match_texture_path(*map, txs);
		(*map_line_start)++;
		if (validate_all_textures_are_found(txs))
			break ;
		map++;
	}
	return (true);
}
