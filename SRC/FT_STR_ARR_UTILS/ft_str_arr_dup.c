/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:51:08 by smoore            #+#    #+#             */
/*   Updated: 2025/05/28 15:35:29 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	**ft_str_arr_partial_dup(char **str_arr, int start)
{
	char	**dup;
	int		len;

	if (!str_arr)
		return (NULL);
	len = ft_str_arr_len((const char **)str_arr);
	if (len <= start)
		return (NULL);
	dup = ft_str_arr_dup(&str_arr[start]);
	return (dup);
}

static char	**ft_str_arr_dup_core(const char **str_arr)
{
	const char	**result;
	const char	**tmp;
	int			len;

	if (!str_arr)
		return (NULL);
	len = ft_str_arr_len(str_arr);
	result = malloc(sizeof(char *) * (len + 1));
	if (!result)
		return (NULL);
	tmp = result;
	while (*str_arr)
	{
		*tmp = ft_strdup(*str_arr);
		tmp++;
		str_arr++;
	}
	*tmp = NULL;
	return ((char **)result);
}

char	**ft_str_arr_dup(char **str_arr)
{
	char	**result;

	result = ft_str_arr_dup_core((const char **)str_arr);
	return (result);
}
