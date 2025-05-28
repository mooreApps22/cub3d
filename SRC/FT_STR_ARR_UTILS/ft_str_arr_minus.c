/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_minus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:43:29 by smoore            #+#    #+#             */
/*   Updated: 2025/05/24 19:04:30 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	**copy_str_arr(const char **str_arr, const char *str, char **result)
{
	int		j;
	int		skip;

	j = 0;
	skip = 0;
	while (*str_arr)
	{
		if (!skip && ft_strcmp(*str_arr, str) == 0)
		{
			skip = 1;
			str_arr++;
			continue ;
		}
		result[j] = ft_strdup(*str_arr);
		if (!result[j])
		{
			ft_str_arr_partial_free(result, j);
			return (NULL);
		}
		str_arr++;
		j++;
	}
	result[j] = NULL;
	return (result);
}

static char	**ft_str_arr_minus_core(const char **str_arr, const char *str)
{
	char	**result;
	int		len;

	if (!str || !str_arr)
		return (NULL);
	len = ft_str_arr_len(str_arr);
	result = malloc(sizeof(char *) * (len + 1));
	if (!result)
		return (NULL);
	result = copy_str_arr(str_arr, str, result);
	if (!result)
		return (NULL);
	return (result);
}

char	**ft_str_arr_minus(char **str_arr, char *str)
{
	char	**result;

	result = ft_str_arr_minus_core((const char **)str_arr, (const char *)str);
	ft_str_arr_free(&str_arr);
	return (result);
}
