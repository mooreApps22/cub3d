/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:57:39 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/20 13:15:33 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

// static bool	is_line_blank(char* line)
// {
// 	int i;

// 	i = 0;
// 	while(line[i])
// 	{
// 		if (line[i] == '\n')
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

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

static int	parse_line(t_cube* data, char* line, int *error_flag)
{
	int		i;

	i = 0;
	while (line[i])
	{
		while(is_blank(line[i]))
			i++;
		if (line[i] == 'N' && line[i + 1] == 'O' && data->textures.north_wall == NULL)
			data->textures.north_wall = extract_path(line, &i);
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

void	parse_textures(t_cube* data, int fd, char **line)
{
	bool	error_flag;
	char	**vals;

	error_flag = 0;
	init_textures(data);
	while (true)
	{
		if (all_textures_found(data->textures))
			break ;
		*line = get_next_line(fd);
		if (!line)
			break ;
		if (parse_line(data, *line, &error_flag) == 0)
		{
			error_flag++;
			break ;
		}
		free(*line);
	}
}

void	parse_main(t_cube *data, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_cleanup("Error - Opening File at Parse\n", data, errno);
	parse_textures(data, fd, &line);
	// parse_map(data, fd, &line);

	close(fd);
}