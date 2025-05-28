/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:28:34 by smoore            #+#    #+#             */
/*   Updated: 2025/05/26 20:56:52 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
	t_image	*north_wall;
	t_image	*south_wall;
	t_image	*west_wall;
	t_image	*east_wall;
	t_rgb	*floor;
	t_rgb	*ceiling;
*/
bool	all_texture_assignment_complete(t_tex *tx)
{
	if (!tx->north_wall || !tx->south_wall || !tx->west_wall
		|| !tx->east_wall || !tx->floor || !tx->ceiling)
		return (false);
	return (true);
}

static bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

static int	skip_blanks(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

static bool	is_valid_xpm_path(char *path)
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

static bool	assign_texture(t_image **texture, char *path)
{
	if (*texture)
	{
		ft_putstr_fd("Error - texture already assigned.\n", 2); 
		return(false);
	}
	*texture = malloc(sizeof(t_image));
	if (!*texture)
	{
		ft_putstr_fd("Error - assigned texture failed malloc.\n", 2);
		return(false);
	}
	(*texture)->path = ft_strdup(path);
	if (!(*texture)->path)
	{
		free(*texture);
		*texture = NULL;
		{
			ft_putstr_fd("Error - assigned texture failed strdup.\n", 2);
			return(false);
		}
	}
	ft_printf("%s texture path successfully assigned!\n", (*texture)->path);
	return (true);
}

char	*cut_newline_off_of_path(char *raw_path)
{
	char	*trim;	

	trim = ft_strtrim(raw_path, " \t\n\r");
	if (!trim || ft_strlen(trim) == 0)
	{
		ft_putstr_fd("Error - texture path trim failed or path is empty.\n", 2); 
		return(NULL);
	}
	ft_printf("Trimmed path: [%s]\n", trim);
	return (trim);
}

static bool	check_xpm_path(t_cube *data, char *id, char *line, int i)
{
	char	*path;
	bool	result;

	result = false;
	path = cut_newline_off_of_path(&line[i]);
	if (!is_valid_xpm_path(path))
	{
		ft_printf("Invalid path: [%s]\n", path);
		free(path);
		return(ft_putstr_fd("Error - xpm path not valid.\n", 2), false);
	}
	if (!ft_strncmp(id, "NO", 2))
	{
		ft_printf("Attempting NO assignment\n");
		result = assign_texture(&data->textures.north_wall, path);
	}
	else if (!ft_strncmp(id, "SO", 2))
	{
		
		ft_printf("Attempting SO assignment\n");
		result = assign_texture(&data->textures.south_wall, path);
	}
	else if (!ft_strncmp(id, "WE", 2))
	{
		
		ft_printf("Attempting WE assignment\n");
		result = assign_texture(&data->textures.west_wall, path);
	}
	else if (!ft_strncmp(id, "EA", 2))
	{
		
		ft_printf("Attempting EA assignment...\n");
		result = assign_texture(&data->textures.east_wall, path);
	}
	else 
		ft_printf("Invalid ID in line: %s\n", line);
	free(path);
	return (result);
}

bool	parse_texture_line(t_cube *data, char *line)
{
	int		i;

	i = 0;
	i = skip_blanks(line, i);
	ft_printf("\n");
	if (!line[i])
		return (true);
//	ft_printf("Checking character at position %d: '%c'\n", i + 2, line[i + 2]);
	if (ft_strncmp(&line[i], "NO", 2) == 0 && is_blank(line[i + 2]))
	{
		ft_putstr_fd("Found NO id.\n", 2);
		return (check_xpm_path(data, "NO", line, i + 2));
	}
//	ft_printf("Checking character at position %d: '%c'\n", i + 2, line[i + 2]);
	if (ft_strncmp(&line[i], "SO", 2) == 0  && is_blank(line[i + 2]))
	{
		ft_putstr_fd("Found SO texture.\n", 2);
		return (check_xpm_path(data, "SO", line, i + 2));
	}
//	ft_printf("Checking character at position %d: '%c'\n", i + 2, line[i + 2]);
	if (ft_strncmp(&line[i], "WE", 2)  == 0 && is_blank(line[i + 2]))
	{
		ft_putstr_fd("Found WE texture.\n", 2);
		return (check_xpm_path(data, "WE", line, i + 2));
	}
//	ft_printf("Checking character at position %d: '%c'\n", i + 2, line[i + 2]);
	if (ft_strncmp(&line[i], "EA", 2)  == 0 && is_blank(line[i + 2]))
	{
		ft_putstr_fd("Found EA texture.\n", 2);
		return (check_xpm_path(data, "EA", line, i + 2));
	}
//	ft_printf("Checking character at position %d: '%c'\n", i + 2, line[i + 2]);
	if (line[i] == 'F')
	{
		ft_putstr_fd("Found Floor color.\n", 2);
		return (assign_rgb(&data->textures.floor, &line[skip_blanks(line, i + 1)]));
	}
//	ft_printf("Checking character at position %d: '%c'\n", i + 2, line[i + 2]);
	if (line[i] == 'C')
	{
		ft_putstr_fd("Found Ceiling color.\n", 2);
		return (assign_rgb(&data->textures.ceiling, &line[skip_blanks(line, i + 1)]));
	}
//	ft_printf("Checking character at position %d: '%c'\n", i + 2, line[i + 2]);
	// need to check all the assignment are made, if it reach here and the assignments are incomplete, there return false otherwise return true
	if (all_texture_assignment_complete(&data->textures))
		return (true);
	return(ft_putstr_fd("Error - parse_texture_line() failed.\n", 2), false);
}
