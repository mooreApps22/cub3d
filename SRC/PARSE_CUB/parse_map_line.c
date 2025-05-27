/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:02:26 by smoore            #+#    #+#             */
/*   Updated: 2025/05/26 20:30:51 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W'
		|| c == '\n' || c == ' ');
}

static bool	line_valid(char *line)
{
	while (*line)
	{
		if (!is_valid_map_char(*line))
			return (ft_putstr_fd("Error -is_valid_map_char failed.\n", 2), false);
		line++;
	}
	return (true);
}


static bool	line_begins_and_ends_with_wall(char *line)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(line) - 1;
	while (line[start] == ' ')
		start++;
	while (line[end] == ' ' || line[end] == '\n')
		end--;
	if (start > end)
		return (ft_putstr_fd("Error - start > end.\n", 2), false);
	return (line[start] == '1' && line[end] == '1');
}

bool	is_line_border(char *line)
{
	int	i;

	i = 0;
	if (!line)
	{
		ft_putstr_fd("Error - Null line passed to is_line_border.\n", 2);
		return (NULL);
	}
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\n' && line[i] != '\t' && line[i] != '\r') //
			return (ft_putstr_fd("Error - borderline 1 screwed up.\n", 2), false);
		i++;
	}
	return (true);
}

bool	parse_map_line(t_cube *data, char *line)
{
	int		len;
	char	*prev_line;
	char	*dup;

	if (!line_valid(line))
		return (ft_putstr_fd("Error - Invalid map character\n", 2), false);
	len = ft_strlen(line);
	if (len > data->map.width)
		data->map.width = len;
	if (data->map.height == 0 && !is_line_border(line))
		return (ft_putstr_fd("Error - First map border line must be all 1'sXXX.\n", 2), false); //
	if (data->map.height > 1 && data->map.data)
	{
		prev_line = data->map.data[data->map.height - 2];	
		if (!prev_line || !line_begins_and_ends_with_wall(prev_line))
			return (ft_putstr_fd("Error - Map lines must end with 1's.\n", 2), false);
	}
	dup = ft_strdup(line);
	if (!dup)
		return (ft_putstr_fd("Error - Invalid map line dup.\n", 2), false);
	data->map.data = ft_str_arr_add(data->map.data, dup);
	if (!data->map.data)
	{
		free(dup);
		return (ft_putstr_fd("Error - bad dup in parse_map_line.\n", 2), false);
	}
	data->map.height++;
	return (true);	
}
