/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:31:02 by smoore            #+#    #+#             */
/*   Updated: 2025/05/26 17:17:13 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static bool	chk_val(int color)
{
	return(color >= 0 && color <= 255);
}

bool	assign_rgb(t_rgb **val, char *line)
{
	char	**split;
	int		i;

	if (*val)
		return (false);
	split = ft_split(line, ',');
	if (!split || ft_str_arr_len((const char **)split) != 3)
		return (false);
	*val = malloc(sizeof(t_rgb));
	if (!*val)
		return (ft_str_arr_free(&split), false);
	i = 0;
	while (i < 3)
	{
		(*val)->r = ft_atoi(split[0]);
		(*val)->g = ft_atoi(split[1]);
		(*val)->b = ft_atoi(split[2]);
		if (!chk_val(((*val)->r) || !chk_val(((*val)->g)) || !chk_val(((*val)->b))))
			return (ft_str_arr_free(&split),free(*val) , *val = NULL, false);
		i++;
	}
	printf("All color assignments made.\n");
	return (ft_str_arr_free(&split), true);
}
