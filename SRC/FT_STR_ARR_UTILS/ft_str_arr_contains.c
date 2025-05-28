/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_contains.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:46:22 by smoore            #+#    #+#             */
/*   Updated: 2025/05/24 19:23:27 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	ft_str_arr_contains(char **str_arr, char *str)
{
	while (*str_arr)
	{
		if (ft_strcmp(*str_arr, str) == 0)
			return (true);
		str_arr++;
	}
	return (false);
}
