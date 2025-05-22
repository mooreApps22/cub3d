/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:57:39 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/22 12:04:28 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// static bool	is_blank(char c)
// {
// 	return (c == ' ' || c == '\t');
// }

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

static t_dir	find_direction(char *dir)
{
	if (dir == NULL)
		return (UNKNOWN);
	if (dir[0] == 'N' && dir[1] == 'O' && dir[2] == '\0')
		return (NORTH);
	else if (dir[0] == 'S' && dir[1] == 'O' && dir[2] == '\0')
		return (SOUTH);
	else if (dir[0] == 'W' && dir[1] == 'E' && dir[2] == '\0')
		return (WEST);
	else if (dir[0] == 'E' && dir[1] == 'A' && dir[2] == '\0')
		return (EAST);
	else if (dir[0] == 'F' && dir[1] == '\0')
		return (FLOOR);
	else if (dir[0] == 'C' && dir[1] == '\0')
		return (CEILING);
	return (UNKNOWN);
}

// static char* extract_path(char* line, int* i)
// {
// 	int start;

// 	*i += 2;
// 	while(is_blank(line[i]))
// 		(*i)++;
// 	start = *i;			
// 	while(line[*i] && line[*i]!= '\n' && !is_blank(line[*i]))
// 		(*i)++;
// 	return (ft_substr(line, start, *i - start));
// }

static int	dptr_len(void **dptr)
{
	int	len;

	if (dptr == NULL)
		return (-1);
	len = 0;
	while (dptr[len] != NULL)
	{
		len++;
	}
	return (len);
}

static void	add_rgb(t_cube *data, char **split, t_dir dir, int *error_flag)
{
	char	**rgb;

	if (dptr_len((void **)split) != 2)
	{
		(*error_flag)++;
		return ;
	}
	rgb = ft_split(split[1], ',');
	if (rgb == NULL || dptr_len((void **) rgb) != 3)
	{
		(*error_flag)++;
		free_dptr((void **) rgb);
		return ;
	}
	if (dir == FLOOR)
	{
		if (data->textures.floor != NULL)
		{
			free(data->textures.floor);
			(*error_flag)++;
		}
		data->textures.floor->r = ft_atoi(rgb[0]);
		data->textures.floor->g = ft_atoi(rgb[1]);
		data->textures.floor->b = ft_atoi(rgb[2]);
	}
	else if (dir == CEILING)
	{
		if (data->textures.ceiling != NULL)
		{
			free(data->textures.ceiling);
			(*error_flag)++;
		}
		data->textures.ceiling->r = ft_atoi(rgb[0]);
		data->textures.ceiling->g = ft_atoi(rgb[1]);
		data->textures.ceiling->b = ft_atoi(rgb[2]);
	}
}

static void	add_path(t_cube *data, char **split, t_dir dir, int *error_flag)
{
	if (dptr_len((void **)split) != 2)
	{
		(*error_flag)++;
		return ;
	}
	if (dir == NORTH)
	{
		if (data->textures.north_wall != NULL)
		{
			free(data->textures.north_wall);
			(*error_flag)++;
		}
		data->textures.north_wall = split[1];
	}
	else if (dir == SOUTH)
	{
		if (data->textures.south_wall != NULL)
		{
			free(data->textures.south_wall);
			(*error_flag)++;
		}
		data->textures.south_wall = split[1];
	}
	else if (dir == EAST)
	{
		if (data->textures.east_wall != NULL)
		{
			free(data->textures.east_wall);
			(*error_flag)++;
		}
		data->textures.east_wall = split[1];
	}
	else if (dir == WEST)
	{
		if (data->textures.west_wall != NULL)
		{
			free(data->textures.west_wall);
			(*error_flag)++;
		}
		data->textures.west_wall = split[1];
	}
}

static int	parse_line(t_cube *data, char *line, int *error_flag)
{
	char	**split;
	t_dir	dir;

	split = ft_split(line, ' ');
	if (split == NULL)
	{
		(*error_flag)++;
		return (0);
	}
	if (split[0] == NULL)
	{
		free_dptr((void **)split);
		return (1);
	}
	dir = find_direction(split[0]);
	if (dir == NORTH || dir == EAST || dir == SOUTH || dir == WEST)
		add_path(data, split, dir, error_flag);
	else if (dir == FLOOR || dir == CEILING)
		add_rgb(data, split, dir, error_flag);
	else
		(*error_flag)++;
	if ((*error_flag) != 0)
	{
		free_dptr((void **)split);
		return (0);
	}
	return (1);
}

void	parse_textures(t_cube* data, int fd, char **line)
{
	int	error_flag;

	error_flag = 0;
	init_textures(data);
	while (true)
	{
		if (all_textures_found(&data->textures))
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

	printf("Value held by NORTH PTR %s\n", data->textures.north_wall);
	printf("Value held by SOUTH PTR %s\n", data->textures.south_wall);
	printf("Value held by WEST PTR %s\n", data->textures.west_wall);
	printf("Value held by EAST PTR %s\n", data->textures.east_wall);

	close(fd);
}
