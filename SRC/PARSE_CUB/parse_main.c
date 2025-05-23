/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:57:39 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/23 18:33:00 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
		data->textures.floor = safe_malloc(sizeof(t_rgb), 1);
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
		data->textures.ceiling = safe_malloc(sizeof(t_rgb), 1);
		data->textures.ceiling->r = ft_atoi(rgb[0]);
		data->textures.ceiling->g = ft_atoi(rgb[1]);
		data->textures.ceiling->b = ft_atoi(rgb[2]);
	}
	free_dptr((void **) rgb);

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
			free(data->textures.north_wall->path);
			(*error_flag)++;
		}
		data->textures.north_wall = safe_malloc(sizeof(t_image), 1);
		data->textures.north_wall->path = ft_strdup(split[1]);

	}
	else if (dir == SOUTH)
	{
		if (data->textures.south_wall != NULL)
		{
			free(data->textures.south_wall);
			(*error_flag)++;
		}
		data->textures.south_wall = safe_malloc(sizeof(t_image), 1);
		data->textures.south_wall->path = ft_strdup(split[1]);
	}
	else if (dir == EAST)
	{
		if (data->textures.east_wall != NULL)
		{
			free(data->textures.east_wall);
			(*error_flag)++;
		}
		data->textures.east_wall = safe_malloc(sizeof(t_image), 1);
		data->textures.east_wall->path = ft_strdup(split[1]);
	}
	else if (dir == WEST)
	{
		if (data->textures.west_wall != NULL)
		{
			free(data->textures.west_wall);
			(*error_flag)++;
		}
		data->textures.west_wall = safe_malloc(sizeof(t_image), 1);
		data->textures.west_wall->path = ft_strdup(split[1]);
	}
}

static int	parse_line(t_cube *data, char *line, int *error_flag)
{
	char	**split;
	t_dir	dir;

	split = ft_split(line, ' ');
	if (split == NULL)
		return (0);
	if (split[0] == NULL)
	{
		free_dptr((void **)split);
		return (1);
	}
	dir = find_direction(split[0]);
//	printf("DIR VARIABLE IS %d\n", dir);
	if (dir == NORTH || dir == EAST || dir == SOUTH || dir == WEST)
		add_path(data, split, dir, error_flag);
	else if (dir == FLOOR || dir == CEILING)
		add_rgb(data, split, dir, error_flag);
	else
		(*error_flag)++;
	printf("ERROR FLAG VALUE IS %d\n", *error_flag);
	free_dptr((void **)split);
	return (1);
}

void	parse_textures(t_cube* data, int fd, char **line)
{
	int	error_flag;

	error_flag = 0;
	while (true)
	{
		if (all_textures_found(&data->textures))
			break ;
		*line = get_next_line(fd);
		if (!line)
			exit_cleanup("Error - Reading .cub file!", data, 2);
		if (parse_line(data, *line, &error_flag) == 0)
		{
			error_flag++;
			break ;
		}
		free(*line);
	}
	if (error_flag != 0)
	{
		while (*line)
		{
			free(*line);
			*line = get_next_line(fd);
		}
		exit_cleanup("Parsing went wrong\n", data, 3);
	}
}

void	parse_main(t_cube *data, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_cleanup("Error - Open failed in parse!\n", data, errno);
	line = NULL;
	parse_textures(data, fd, &line);
	line = NULL; // smoore added
	parse_map(data, fd, &line);

	

	// printf("Value held by NORTH PTR %s\n", data->textures.north_wall);
	// printf("Value held by SOUTH PTR %s\n", data->textures.south_wall);
	// printf("Value held by WEST PTR %s\n", data->textures.west_wall);
//	 printf("Value held by EAST PTR %s\n", data->textures.east_wall->path);

	// printf("Value held by CEILING R PTR %d\n", data->textures.ceiling->r);
	// printf("Value held by CEILING G PTR %d\n", data->textures.ceiling->g);
	// printf("Value held by CEILING B PTR %d\n", data->textures.ceiling->b);

	// printf("Value held by GROUND R PTR %d\n", data->textures.floor->r);
	// printf("Value held by GROUND G PTR %d\n", data->textures.floor->g);
	// printf("Value held by GROUND B PTR %d\n", data->textures.floor->b);


	close(fd);
}
