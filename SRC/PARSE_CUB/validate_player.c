/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:32:32 by smoore            #+#    #+#             */
/*   Updated: 2025/05/29 18:20:24 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	is_valid_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	calculate_player_direction(t_map *map, int i, int j,
	int *count, t_ply *player)
{
	char c;

	(*count)++;
	if (*count > 1)
		return (error_msg(0, "Too many player chars in map.", NULL));
	c = map->data[i][j];
	ft_printf("Player char: %c\n", c);
	if (c == 'N')
		player->alpha = M_PI / 2;
	else if (c == 'S')
		player->alpha = -M_PI / 2;
	else if (c == 'E')
		player->alpha = 0;
	else if (c == 'W')
		player->alpha = M_PI;
	printf("Player Alpha: %f\n", player->alpha);
	return (true);
}

bool	validate_player(t_map *map, t_ply *player)
{
	int	i;
	int	j;
	int	count;

	if (!map || !map->data)
		return (error_msg(0, "Null passed into validate_player().", NULL));
	i = 0;
	count = 0;
	while (map->data[i])
	{
		j = 0;
		while (map->data[i][j])
		{
			if (is_valid_player_char(map->data[i][j]))
				if (!calculate_player_direction(map, i, j, &count, player))	
					return (error_msg(0, "Failed to validate player.", NULL));
			j++;
		}
		i++;
	}
	if (count == 0)
		return (error_msg(0, "Zero player char in map.", NULL));
	return (true);
}
