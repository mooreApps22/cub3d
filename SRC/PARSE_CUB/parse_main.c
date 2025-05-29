/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:13:43 by smoore            #+#    #+#             */
/*   Updated: 2025/05/29 14:17:44 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	extract_remaining_lines(t_map *map, t_tex *txs)
{
	char **dup;

	if (!txs || !map->data)
		return (error_msg(0, "Map data or textures missing.", NULL));
	dup = ft_str_arr_partial_dup(map->data, 6);
	if (!dup)
		return (error_msg(0, "Dup failed malloc.", NULL));
	ft_str_arr_printf(dup);
	ft_str_arr_free(&map->data);
	map->data = dup;
	return (true);
}

bool	validate_all_ones_line(char *line)
{
	int i;

	if (!line)
		return (error_msg(0, "Validate all ones, passed null line.", NULL));
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
			return (error_msg(0, "Top/Bottom map line should be 1's & spaces.", NULL));
		i++;
	}
	// ft_printf("Found top/bottom: %s\n", line);
	return (true);
}

bool	check_mid_line_char(char c)
{
	return (c != '0' && c != '1' && c != ' '
		&& c != '\n' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W');
}

bool	validate_mid_line(char *line)
{
	int i;

	if (!line)
		return (error_msg(0, "Validate mid_line, passed null line.", NULL));
	i = 0;
	while (line[i])
	{
		if (check_mid_line_char(line[i]))
			return (error_msg(0, "Mid map line should have 1 0NSEWnewline.", NULL));
		i++;
	}
	// ft_printf("Found mid line: %s\n", line);
	return (true);
}

bool	validate_map_lines(t_map *map)
{
	int	i;

	if (!map)
			return (error_msg(0, "Validate Map lines passed null map.", NULL));
	i = 0;
	while (map->data[i])
	{
		if ((i == 0 || i == ft_str_arr_len((const char **)map->data)))
		{
			if (!validate_all_ones_line(map->data[i]))
				return (error_msg(0, "Failed to validate all top/bottom line.", NULL));
		}
		else
		{
			if (!validate_mid_line(map->data[i]))
				return (error_msg(0, "Failed to validate mid line.", NULL));
		}
		i++;
	}
	return (true);
}

bool	validate_space_border_lines(t_map *map)
{
	int	i;

	if (!map)
		return (error_msg(0, "Validate space border lines passed null map.", NULL));
	i = 0;
	while (map->data[i])
	{
		if ((i > 0 && i < ft_str_arr_len((const char **)map->data)))
		{
			// ft_printf("If line contains ' ' check the space in the [i - 1] && [i + 1] for a '1'\n");	
		}
		i++;
	}
	return (true);
}

bool	validate_cub_data(t_map *map, t_tex *txs)
{
	if (!map)
		return (error_msg(0, "No map to validate.", NULL));
	if (!trim_first_six_lines(map->data))
		return (error_msg(0, "Failed to trim first six lines.", NULL));
	if (!validate_first_six_lines(map->data, txs))
		return (error_msg(0, "Failed to validate 1st six lines.", NULL));
	if (!extract_remaining_lines(map, txs))
		return (error_msg(0, "Failed to extract lines.", NULL));
	if (!validate_map_lines(map))
		return (error_msg(0, "Failed to validate map lines.", NULL));
	if (!validate_space_border_lines(map))
		return (error_msg(0, "Failed to check space borders.", NULL));
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
