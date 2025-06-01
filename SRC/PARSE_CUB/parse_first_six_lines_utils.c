/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_first_six_lines_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:13:43 by smoore            #+#    #+#             */
/*   Updated: 2025/06/01 17:11:59 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	trim_first_six_lines(char **map)
{
	int		i;
	char	*trim;

	i = 0;
	while (i < 6)
	{
		trim = ft_strtrim(map[i], " \n\t\r");
		printf("TRIM: %s\n", trim);
		if (!trim)
			return (error_msg(0, "failed to trim texture line.", NULL));
		if (map[i])
		{
			free(map[i]);
			map[i] = trim;
		}
		i++;
	}
	return (true);
}

bool	assign_texture_path(char *line, char *id, char **tex_path)
{
	int	i;

	if (ft_strncmp(line, id, ft_strlen(id)) == 0 && !*tex_path)
	{
		i = ft_strlen(id);
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		*tex_path = ft_strdup(line + i);
		if (!*tex_path)
			return (error_msg(0, "Failed to dup texture path.", NULL));
		return (true);
	}
	return (false);
}

bool	chk_val(int color)
{
	return (color >= 0 && color <= 255);
}

bool	process_color_values(t_rgb *val, char **split, int len)
{
	int	modified_r;

	modified_r = ft_atoi(ft_strchr(split[len - 3], ' '));
	(val)->b = ft_atoi(split[len - 1]);
	(val)->g = ft_atoi(split[len - 2]);
	(val)->r = modified_r;
	if (!chk_val(val->r) || !chk_val(val->g) || !chk_val(val->b))
	{
		ft_str_arr_free(&split);
		return (false);
	}
	ft_printf("r: %d, g: %d, b: %d\n", val->r, val->g, val->b);
	return (true);
}

bool	assign_color_values(char *line, char *id, t_rgb *val)
{
	char	**split;
	int		len;

	if (ft_strncmp(line, id, ft_strlen(id)) == 0
		&& (val->r == -1 && val->g == -1 && val->b == -1))
	{
		split = ft_split(line, ',');
		len = ft_str_arr_len((const char **)split);
		if (!split || len < 3)
		{
			ft_str_arr_free(&split);
			return (error_msg(0, "Failed to slip color values.", NULL));
		}
		if (!process_color_values(val, split, len))
			return (error_msg(0, "RGB values have to be 0-255.", NULL));
		ft_str_arr_free(&split);
		return (true);
	}
	return (false);
}
