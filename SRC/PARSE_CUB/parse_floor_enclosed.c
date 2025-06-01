/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_enclosed.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:28:34 by smoore            #+#    #+#             */
/*   Updated: 2025/06/01 12:32:12 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
