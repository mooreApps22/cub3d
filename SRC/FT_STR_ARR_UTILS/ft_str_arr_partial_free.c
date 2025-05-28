/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_partial_free.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:46:04 by smoore            #+#    #+#             */
/*   Updated: 2025/05/24 17:19:14 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_str_arr_partial_free(char **str_arr, int count)
{
	while (count--)
		free(str_arr[count]);
	free(str_arr);
}
