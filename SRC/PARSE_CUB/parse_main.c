/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:57:39 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/26 17:48:10 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
			return (false);
		}
		free(line);
	}
	return (true);
}

void	parse_main(t_cube *data, char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_cleanup("Error - Open failed in parse!\n", data, errno);
	if (get_texture_data(data, fd))
		exit_cleanup("Error - Failed to parse textures!\n", data, errno);
//	if (get_map_data(data, filename, fd) == 0)	
//		exit_cleanup("Error - failed to get map data\n", data, errno);
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

	close(fd);
}
