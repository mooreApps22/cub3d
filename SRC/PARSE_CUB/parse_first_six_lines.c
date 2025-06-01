/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_first_six_lines.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:13:43 by smoore            #+#    #+#             */
/*   Updated: 2025/06/01 17:09:06 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
	return (txs->north_wall->path
		&& txs->south_wall->path
		&& txs->east_wall->path
		&& txs->west_wall->path
		&& txs->ceiling->r >= 0
		&& txs->ceiling->g >= 0
		&& txs->ceiling->b >= 0
		&& txs->floor->r >= 0
		&& txs->floor->g >= 0
		&& txs->floor->b >= 0);
}

bool	validate_first_six_lines(char **map, t_tex *txs, int *map_line_start)
{
	printf("init_textures%p\n", txs);
	if (!init_textures(txs))
		return (error_msg(0, "t_tex failed malloc.", NULL));
	while (*map)
	{
		if (match_texture_path(*map, txs))
		{
			(*map_line_start)++;
			if (validate_all_textures_are_found(txs))
				break ;
		}
		map++;
	}
	if (!validate_all_textures_are_found(txs))
		return (error_msg(0, "Failed to match texture paths.", NULL));
	return (true);
}
