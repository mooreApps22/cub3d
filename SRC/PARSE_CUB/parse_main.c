/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:13:43 by smoore            #+#    #+#             */
/*   Updated: 2025/05/31 20:13:42 by smoore           ###   ########.fr       */
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
		return (error_msg(0, "Invalid map_line_start index in extract_remaining_lines.", NULL));
	dup = ft_str_arr_partial_dup(map->data, map->map_line_start); //
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

bool	is_valid_tile(char c)
{
	return (c == '0' || c == '1' ||  c == 'N'
		||  c == 'S' ||  c == 'E' ||  c == 'W');
}

bool	check_bounds_are_valid(t_map *map, int i, int j)
{
	if (i < 0 || j < 0)	
		return (false);
	if (!map->data[i] || j >= (int)ft_strlen(map->data[i]))
		return (false);
	if (!is_valid_tile(map->data[i][j]))
		return (false);
	return (true);
}


bool	is_tile_enclosed(t_map *map, int i, int j)
{
	if (!check_bounds_are_valid(map, i - 1, j))
		return (false);
	if (!check_bounds_are_valid(map, i + 1, j))
		return (false);
	if (!check_bounds_are_valid(map, i, j - 1))
		return (false);
	if (!check_bounds_are_valid(map, i, j + 1))
		return (false);
	return (true);
}


bool	validate_floor_tiles_are_enclosed(t_map *map)
{
	int	i;
	int	j;

	if (!map || !map->data)
		return (error_msg(0, "Map is null in enclosure check.", NULL));
	i = 0;
	while (map->data[i])
	{
		j = 0;
		while (map->data[i][j])
		{
			if (map->data[i][j] == '0')
			{
				if (!is_tile_enclosed(map, i, j))
					return (error_msg(0, "Unenclosed floor tile found.", NULL));
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	validate_xpm_extension(char *path)
{
	int	fd;
	int	len;

	if (!path)
	{
		ft_putstr_fd("Error - no path provided.\n", 2); 
		return(false);
	}
	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		ft_putstr_fd("Error - texture path doesn't end with .xpm.\n", 2); 
		return(false);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error - failed to open xpm path.\n", 2);
		return(false);
	}
	close(fd);
	ft_printf("Was able to validate .xpm path!!\n");
	return (true);
}

bool	validate_xpm_extensions(t_tex *txs)
{
	if (!txs || !txs->north_wall || !txs->south_wall ||
		!txs->east_wall || !txs->west_wall)
		return (error_msg(0, "Missing texture structures", NULL));
	if (!txs)
		return (error_msg(0, "failed to pass t_tex of .xpm validation", NULL));
	if (!validate_xpm_extension(txs->north_wall->path))
		return (error_msg(0, "failed to validate north wall xpm ext", NULL));
	if (!validate_xpm_extension(txs->south_wall->path))
		return (error_msg(0, "failed to validate south wall xpm ext", NULL));
	if (!validate_xpm_extension(txs->east_wall->path))
		return (error_msg(0, "failed to validate east wall xpm ext", NULL));
	if (!validate_xpm_extension(txs->west_wall->path))
		return (error_msg(0, "failed to validate west wall xpm ext", NULL));
	return (true);
}

bool	validate_map_dimensions(t_map *map)
{
	int current_width;

	if (!map)
		ft_putstr_fd("Error - failed to pass map.\n", 2);
	current_width = 0;
	while (map->data[map->height])
	{
		current_width = ft_strlen(map->data[map->height]);
		if (current_width >  map->width)
			map->width = current_width;
		map->height++;
	}
	return (true);
}

bool	load_all_textures(t_tex *txs, void *mlx)
{	
	if (!load_texture(txs->north_wall, mlx, txs->north_wall->path))
		return (error_msg(0, "Failed get north_wall addr.", NULL));
	if (!load_texture(txs->south_wall, mlx, txs->south_wall->path))
		return (error_msg(0, "Failed get south_wall addr.", NULL));
	if (!load_texture(txs->east_wall, mlx, txs->east_wall->path))
		return (error_msg(0, "Failed get east_wall addr.", NULL));
	if (!load_texture(txs->west_wall, mlx, txs->west_wall->path))
		return (error_msg(0, "Failed get west_wall addr.", NULL));
	return (true);
}

bool	validate_cub_data(t_map *map, t_tex *txs, t_ply *player, t_mlx *mlx)
{
	if (!map)
		return (error_msg(0, "No map to validate.", NULL));
	if (!trim_first_six_lines(map->data))
		return (error_msg(0, "Failed to trim first six lines.", NULL));
	if (!validate_first_six_lines(map->data, txs, &map->map_line_start))
		return (error_msg(0, "Failed to validate 1st six lines.", NULL));
	if (!extract_remaining_lines(map, txs))
		return (error_msg(0, "Failed to extract lines.", NULL));
	if (!validate_map_lines(map))
		return (error_msg(0, "Failed to validate map lines.", NULL));
	if (!validate_floor_tiles_are_enclosed(map))
		return (error_msg(0, "Failed to validate floor tiles.", NULL));
	if (!validate_player(map, player))
		return (error_msg(0, "Failed to validate player.", NULL));
	if (!validate_map_dimensions(map))
		return (error_msg(0, "Failed to validate map dimensions.", NULL));
	if (!load_all_textures(txs, mlx->mlx_ptr))
		return (error_msg(0, "Failed to load all textures.", NULL));
	if (!validate_xpm_extensions(txs))
		return (error_msg(0, "Failed to validate .xpm extensions.", NULL));
	return (true);	
}

bool	parse_main(t_cube *data, char *filename)
{
	if (!open_cub_file_and_copy_data(data, filename))
		return (error_msg(0, "failed to extract cub file data.", NULL));
	if (!validate_cub_data(&data->map, &data->textures, &data->player,
		data->mlx_data.mlx_ptr))
		return (error_msg(0, "failed to validate cub data.", NULL));
	return (true);
}
