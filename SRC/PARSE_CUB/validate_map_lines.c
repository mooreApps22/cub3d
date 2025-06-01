/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:36:19 by smoore            #+#    #+#             */
/*   Updated: 2025/06/01 17:20:07 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	extract_remaining_lines(t_map *map, t_tex *txs)
{
	char	**dup;
	int		map_len;

	if (!txs || !map->data)
		return (error_msg(0, "Map data or textures missing.", NULL));
	map_len = ft_str_arr_len((const char **)map->data);
	if (map->map_line_start < 0 || map->map_line_start >= map_len)
		return (error_msg(0, "Invalid map_line_start index \
			in extract_remaining_lines.", NULL));
	dup = ft_str_arr_partial_dup(map->data, map->map_line_start);
	if (!dup)
		return (error_msg(0, "Dup failed malloc.", NULL));
	ft_str_arr_printf(dup);
	ft_str_arr_free(&map->data);
	map->data = dup;
	return (true);
}

bool	validate_all_ones_line(char *line)
{
	int	i;

	if (!line)
		return (error_msg(0, "Validate all ones, passed null line.", NULL));
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
			return (error_msg(0, "Top/Bottom map line should \
				be 1's & spaces.", NULL));
		i++;
	}
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
	int	i;

	if (!line)
		return (error_msg(0, "Validate mid_line, passed null line.", NULL));
	i = 0;
	while (line[i])
	{
		if (check_mid_line_char(line[i]))
			return (error_msg(0, "Mid map line \
				should have 1 0NSEWnewline.", NULL));
		i++;
	}
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
				return (error_msg(0, "Failed to validate\
					all top/bottom line.", NULL));
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
