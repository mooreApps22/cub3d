/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:13:43 by smoore            #+#    #+#             */
/*   Updated: 2025/05/28 11:32:35 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


bool	trim_first_six_lines(char **map)
{
	int		i;
	char	*trim;

	i = 0;
	while (i < 6)
	{
		trim = ft_strtrim(map[i], " \n\t\r");
		printf("TRIM: %s\n", trim);
		if (!trim)
			return (error_msg(0, "failed to trim texture line.", NULL));
		if (map[i])
		{
			free(map[i]);
			map[i] = trim;
		}
		i++;
	}
	return (true);
}

bool	assign_texture_path(char *line, char *id, char **tex_path)
{
	int i;

	if (ft_strncmp(line, id, ft_strlen(id)) == 0 && !*tex_path)
	{
		i = ft_strlen(id);
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		*tex_path = ft_strdup(line + i);
		if (!*tex_path)
			return (error_msg(0, "Failed to dup texture path.", NULL));
		return (true);
	}
	return (false);
}

bool	chk_val(int color)
{
	return (color >= 0 && color <= 255);
}

bool	assign_color_values(char *line, char *id, t_rgb *val)
{
	char	**split;
	int		len;

	if (ft_strncmp(line, id, ft_strlen(id)) == 0 && !val)
	{
		split = ft_split(line, ',');
		len  = ft_str_arr_len((const char **)split);
		if (!split || len < 3)
		{
			ft_str_arr_free(&split);
			return (error_msg(0, "Failed to slip color values.", NULL));
		}
		(val)->b = ft_atoi(split[len - 1]);
		(val)->g = ft_atoi(split[len - 2]);
		(val)->r = ft_atoi(split[len - 3]);
		if (!chk_val(val->r) || !chk_val(val->g) || !chk_val(val->b))
		{
			ft_str_arr_free(&split);
			return (error_msg(0, "RGB values have to be 0-255.", NULL));
		}
		ft_str_arr_free(&split);
	}
	return (false);
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

void	set_init_textures_paths_to_null(t_tex *txs)
{
	txs->north_wall->path = NULL;
	txs->south_wall->path = NULL;
	txs->east_wall->path = NULL;
	txs->west_wall->path = NULL;
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

bool	validate_first_six_lines(char **map, t_tex *txs)
{
	int		i;
	
	i = 0;
	if (!init_textures(txs))
		return (error_msg(0, "t_tex failed malloc.", NULL));
	while (i < 6)
	{
		match_texture_path(map[i], txs);
		i++;
	}
	if (!txs->north_wall->path || !txs->south_wall->path ||
		!txs->east_wall->path || !txs->west_wall->path ||
		!txs->ceiling || !txs->floor)
		return (error_msg(0, "Failed to find all textures.", NULL));
	return (true);
}

bool	validate_cub_data(t_map *map, t_tex *txs)
{
	if (!map)
		return (error_msg(0, "No map to validate.", NULL));
	if (!trim_first_six_lines(map->data))
		return (error_msg(0, "Failed to trim first six lines.", NULL));
	if (!validate_first_six_lines(map->data, txs))
		return (error_msg(0, "Failed to check order of data.", NULL));
	return (true);	
}

bool	parse_main(t_cube *data, char *filename)
{
	if (!open_cub_file_and_copy_data(data, filename))
		return (error_msg(0, "failed to extract cub file data.", NULL));
	if (!validate_cub_data(&data->map, &data->textures))
		return (error_msg(0, "failed to validate cub data.", NULL));
	return (true);
}
