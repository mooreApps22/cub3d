/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:28:34 by smoore            #+#    #+#             */
/*   Updated: 2025/05/26 17:33:02 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*

typedef struct s_map
{
	char			**data;
	unsigned short	height;
	unsigned short	width;
}	t_map;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}	t_rgb;

typedef struct s_tex
{
	t_image	*north_wall;
	t_image	*south_wall;
	t_image	*west_wall;
	t_image	*east_wall;
	t_rgb	*floor;
	t_rgb	*ceiling;
}	t_tex;

typedef struct s_image
{
	char			*path;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
	int				x; //
	int				y; //
	unsigned int	color;
}	t_image;
*/


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
		return (false);
	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (false);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

static bool	assign_texture(t_image **texture, char *path)
{
	if (*texture)
		return (false); // already assigned
	*texture = malloc(sizeof(t_image));
	if (!*texture)
		return (false);
	(*texture)->path = ft_strdup(path);
	if (!(*texture)->path)
	{
		free(*texture);
		*texture = NULL;
		return (false);
	}
	return (true);
}

char	*cut_newline_off_of_path(char *raw_path)
{
	char	*trim;	

	trim = ft_strtrim(raw_path, " \t\n\r");
	if (!trim)
		return (NULL);
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
		return (false);
	}
	if (!ft_strncmp(id, "NO", 2))
		result = assign_texture(&data->textures.north_wall, path);
	else if (!ft_strncmp(id, "SO", 2))
		result = assign_texture(&data->textures.south_wall, path);
	else if (!ft_strncmp(id, "WE", 2))
		result = assign_texture(&data->textures.west_wall, path);
	else if (!ft_strncmp(id, "EA", 2))
		result = assign_texture(&data->textures.east_wall, path);
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
	if (!line[i])
		return (true);
	if (!ft_strncmp(&line[i], "NO", 2))
		return (check_xpm_path(data, "NO", line, i + 2));
	if (!ft_strncmp(&line[i], "SO", 2))
		return (check_xpm_path(data, "SO", line, i + 2));
	if (!ft_strncmp(&line[i], "WE", 2))
		return (check_xpm_path(data, "WE", line, i + 2));
	if (!ft_strncmp(&line[i], "EA", 2))
		return (check_xpm_path(data, "EA", line, i + 2));
	if (line[i] == 'F')
		return (assign_rgb(&data->textures.floor, &line[skip_blanks(line, i + 1)]));
	if (line[i] == 'C')
		return (assign_rgb(&data->textures.ceiling, &line[skip_blanks(line, i + 1)]));
	return (false);
}
