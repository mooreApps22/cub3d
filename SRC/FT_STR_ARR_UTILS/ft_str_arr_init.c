/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:39:00 by smoore            #+#    #+#             */
/*   Updated: 2025/05/24 17:18:49 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	**ft_str_arr_init(void)
{
	char	**str_arr;

	str_arr = malloc(sizeof(char *) * 1);
	if (!str_arr)
		return (NULL);
	str_arr[0] = NULL;
	return (str_arr);
}
