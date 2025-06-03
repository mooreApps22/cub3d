/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_first_six_lines.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:13:43 by smoore            #+#    #+#             */
/*   Updated: 2025/06/03 17:04:41 by smoore           ###   ########.fr       */
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

static void	report_missing_color_values(t_tex *txs)
{
	if (!txs)
		return ;
	if (txs->ceiling->r == -1)
		printf("Missing ceiling red value\n");
	if (txs->ceiling->g == -1)
		printf("Missing ceiling green value\n");
	if (txs->ceiling->b == -1)
		printf("Missing ceiling blue value\n");
	if (txs->floor->r == -1)
		printf("Missing floor red value\n");
	if (txs->floor->g == -1)
		printf("Missing floor green value\n");
	if (txs->floor->b == -1)
		printf("Missing floor blue value\n");
}

static void	report_missing_textures(t_tex *txs)
{
	if (!txs)
		return ;
	if (!txs->north_wall->path)
		printf("Missing pathway to north wall\n");
	if (!txs->south_wall->path)
		printf("Missing pathway to south wall\n");
	if (!txs->east_wall->path)
		printf("Missing pathway to east wall\n");
	if (!txs->west_wall->path)
		printf("Missing pathway to west wall\n");
	report_missing_color_values(txs);
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
	report_missing_textures(txs);
	if (!validate_all_textures_are_found(txs))
		return (error_msg(0, "Failed to match texture paths.", NULL));
	return (true);
}
