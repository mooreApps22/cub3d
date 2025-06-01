/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:32:32 by smoore            #+#    #+#             */
/*   Updated: 2025/06/01 17:43:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	is_valid_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	calculate_player_direction(t_player_info *info, int i, int j)
{
	char	c;

	(*info->count)++;
	if (*info->count > 1)
		return (error_msg(0, "Too many player chars in map.", NULL));
	c = info->map->data[i][j];
	ft_printf("Player char: %c\n", c);
	if (c == 'N')
		info->player->alpha = M_PI / 2;
	else if (c == 'S')
		info->player->alpha = -M_PI / 2;
	else if (c == 'E')
		info->player->alpha = 0;
	else if (c == 'W')
		info->player->alpha = M_PI;
	printf("Player Alpha: %f\n", info->player->alpha);
	info->map->data[i][j] = '0';
	info->player->pos.x = j * TILE_SIZE + TILE_SIZE / 2;
	info->player->pos.y = i * TILE_SIZE + TILE_SIZE / 2;
	return (true);
}

static bool	scan_map_for_player(t_player_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (info->map->data[i])
	{
		j = 0;
		while (info->map->data[i][j])
		{
			if (is_valid_player_char(info->map->data[i][j]))
			{
				if (!calculate_player_direction(info, i, j))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	validate_player(t_map *map, t_ply *player)
{
	int				count;
	t_player_info	info;

	if (!map || !map->data)
		return (error_msg(0, "Null passed into validate_player().", NULL));
	count = 0;
	info.map = map;
	info.player = player;
	info.count = &count;
	if (!scan_map_for_player(&info))
		return (error_msg(0, "Failed to validate player.", NULL));
	if (count == 0)
		return (error_msg(0, "Zero player char in map.", NULL));
	return (true);
}
