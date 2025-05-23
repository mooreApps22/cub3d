/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:17:16 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/23 18:31:17 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_player(char c)
{
	if(c == 'w' || c == 'W' || c == 'n' || c == 'N' || c == 'e' || c == 'E' \
			|| c == 's' || c == 'S')
		return (1);
	return (0);
}

static void	check_character_validity(t_cube *data, char **map, size_t max_line_len)
{
	int		i;
	char	*line;

	if (map == NULL || *map == NULL)
		exit_cleanup("Error - No map!", data, 1);
	i = -1;
	while(map[++i] != NULL)
	{
	/*
		if (ft_strval(map[i], "nNsSwWeE01 ", 3) != 0)
		{
			free_dptr((void **)map);
			exit_cleanup("Error - Illegal Map Character Detected!\n", data, 66);
		}
	*/
		if (max_line_len > ft_strlen(map[i]))
		{
			line = safe_malloc(sizeof(char), max_line_len + 1);
			ft_strlcpy(line, map[i], max_line_len + 1);
			line[max_line_len] = '\0';
			while (--max_line_len > ft_strlen(map[i]))
				line[max_line_len] = ' ';
			free(map[i]);
			map[i] = line;
		}
	}
}

static void	check_around(t_cube *data, char **map, int i, int j)
{
	if (j == 0 || map[j + 1] == NULL || i == 0 || map[j][i + 1] == '\0' || map[j][i + 1] == '\n')
	{
		free_dptr((void **)map);
		exit_cleanup("Error - Map Error\n", data, 68);
	}
	if (map[j][i - 1] == ' ' || map[j][i + 1] == ' ' || map[j - 1][i] == ' ' || map[j + 1][i] == ' ' || map[j][i + 1] == '\0')
	{
		free_dptr((void **)map);
		exit_cleanup("Error - Map Error\n", data, 68);
	}
}

static void	check_map_closure_and_player_singularity(t_cube *data, char **map)
{
	int	playerCount;
	int	i;
	int	j;

	playerCount = 0;
	j = -1;
	while (map[++j] != NULL)
	{
		i = 0;
		while (map[j][i] != '\0')
		{
			if (is_player(map[j][i]))
				playerCount++;
			if (map[j][i] == '0' || is_player(map[j][i]))
			{
				check_around(data, map, i, j);
			}
			i++;
		}
	}
	if (playerCount != 1)
	{
		free_dptr((void **)map);
		exit_cleanup("Error - Player Character Count", data, 67);
	}
}


void	parse_map(t_cube *data, int fd, char **line)
{
	char	**map;
	char	*temp;
	char	*full_line;
	size_t	max_line_len;

	map = NULL;
	/*
	max_line_len = 0;
	if (*line == NULL)
		full_line = get_next_line(fd);
	else
	{
		temp = get_next_line(fd);
		max_line_len = ft_strlen(*line) + ft_strlen(temp);
		full_line = ft_strjoin(*line, temp);
		free(temp);
	}
	*/
	if (*line)
	{
		temp = get_next_line(fd);
		if (!temp)
			full_line = ft_strdup(*line);
		else
		{
			max_line_len = ft_strlen(*line) + ft_strlen(temp);
			full_line = ft_strjoin(*line, temp);
			free(temp);
		}

	}
	else
		full_line = get_next_line(fd);
	while (full_line != NULL)
	{
		if (ft_strlen(full_line) > max_line_len)
			max_line_len = ft_strlen(full_line);
		add_to_dptr((void ***)&map, (void *)full_line);
		full_line = get_next_line(fd);
	}
	check_character_validity(data, map, max_line_len);
	check_map_closure_and_player_singularity(data, map);
	free_dptr((void **)map);
}
