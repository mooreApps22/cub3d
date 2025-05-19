/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:18:20 by smoore            #+#    #+#             */
/*   Updated: 2025/05/19 19:02:53 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
	NO ./TEXTURES/north.xpm

	SO ./TEXTURES/south.xpm

	WE ./TEXTURES/west.xpm

	EA ./TEXTURES/east.xpm

	TO DO:
		check for dups of paths
		does it work in any order
		will it stop once all 4 textures are found

*/

static bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

static bool	is_line_blank(char* line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if (line[i] == '\n')
			return (false);
		i++;
	}
	return (true);
}

static char* extract_path(char* line, int* i)
{
	int start;

	*i += 2;
	while(is_blank(line[i]))
		(*i)++;
	start = *i;			
	while(line[*i] && line[*i]!= '\n' && !is_blank(line[*i]))
		(*i)++;
	return (ft_substr(line, start, *i - start));
}

static int	parse_line(t_cube* data, char* line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		while(is_blank(line[i]))
			i++;
		if (line[i] == 'N' && line[i + 1] == 'O' && !data->textures->no_found)
			data->textures->north_path = extract_path(line, &i);
		else if (line[i] == 'S' && line[i + 1] == 'O' && !data->textures->so_found)
			data->textures->south_path = extract_path(line, &i);
		else if (line[i] == 'W' && line[i + 1] == 'E' && !data->textures->we_found)
			data->textures->west_path = extract_path(line, &i);
		else if (line[i] == 'E' && line[i + 1] == 'A' && !data->textures->ea_found)
			data->textures->east_path = extract_path(line, &i);
		else
			return (0);
		break ;
	}
	return (1);
}

void	parse_textures(t_cube* data, char* filename)
{
	char*	line;		
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_cleanup("Failed to open .cub file in parse_textures", data, 1);
	while (true)
	{
		if (all_found(data->textures))
			break ;
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_line_blank(line))
		{
			free(line);
			continue ;
		}
		if (parse_line(data, line) == 0)
			exit_cleanup("Error parsing line", data, 1);
		free(line);
	}
	close(fd);
}
