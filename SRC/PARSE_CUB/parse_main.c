/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:57:39 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/26 20:37:37 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	count_player_chars(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			count++;
		line++;
	}
	return (count);
}


bool	only_one_player_position(char **map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		count += count_player_chars(map[i]);
		if (count > 1)
		{
			ft_putstr_fd("Error - You can't have more than 1 players.\n", 2);	
			return (false);
		}
		i++;
	}
	if (count == 0)
	{
		ft_putstr_fd("Error - You can't have zero player characters.\n", 2);
		return (false);
	}
	return (true);
}

bool	get_map_data(t_cube *data, int fd)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		if (!parse_map_line(data, line))
		{
			free(line);
			return (ft_putstr_fd("Error - no parse_map_line.\n", 2), false);
		}
		free(line);
	}
	if (!is_line_border(data->map.data[data->map.height -1]))
	{
		ft_putstr_fd("Error - Last border must be all 1's.\n", 2);
		return(false);
	}
	if (!only_one_player_position(data->map.data))
	{
		ft_putstr_fd("Error - Can only have one player character.\n", 2);
		return(false);
	}
	ft_printf("Reached end of file - get_map_data.\n");
	return (true);
}

bool	get_texture_data(t_cube *data, int fd)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		if (!parse_texture_line(data, line))
		{
			free(line);
			ft_putstr_fd("Error - no parse_text_line.\n", 2);
			return (false);
		}
		free(line);
	}
	ft_printf("Reached end of file - get_texture_data.\n");
	return (true);
}

void	parse_main(t_cube *data, char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_cleanup("Error - Open failed in parse!\n", data, errno);
	if (!get_texture_data(data, fd))
		exit_cleanup("Error - Failed to parse textures!\n", data, errno);
	if (!get_map_data(data, fd))
		exit_cleanup("Error - Failed to parse map!\n", data, errno);
	ft_printf("TEX: %s\n", data->textures.north_wall->path);
	ft_printf("TEX: %s\n", data->textures.south_wall->path);
	ft_printf("TEX: %s\n", data->textures.west_wall->path);
	ft_printf("TEX: %s\n", data->textures.east_wall->path);

	ft_printf("C R: %d\n", data->textures.ceiling->r);
	ft_printf("C G: %d\n", data->textures.ceiling->g);
	ft_printf("C B: %d\n", data->textures.ceiling->b);

	ft_printf("F R: %d\n", data->textures.floor->r);
	ft_printf("F G: %d\n", data->textures.floor->g);
	ft_printf("F B: %d\n", data->textures.floor->b);

	ft_str_arr_printf(data->map.data);
	
	close(fd);
}
