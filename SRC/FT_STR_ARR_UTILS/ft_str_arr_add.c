/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:46:04 by smoore            #+#    #+#             */
/*   Updated: 2025/05/24 19:04:45 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	**add_malloc(int len)
{
	char	**result;

	result = malloc(sizeof(char *) * (len + 2));
	if (!result)
		return (NULL);
	return (result);
}

static bool	add_copy(char **result, const char **str_arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		result[i] = ft_strdup(str_arr[i]);
		if (!result[i])
		{
			ft_str_arr_partial_free(result, i);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	append_new_str(char **result, const char *str, int i)
{
	result[i] = ft_strdup(str);
	if (!result[i])
	{
		ft_str_arr_partial_free((char **)result, i);
		return (false);
	}
	result[i + 1] = NULL;
	return (true);
}

static char	**ft_str_arr_add_core(const char **str_arr, const char *str)
{
	char	**result;
	int		len;

	if (!str || !str_arr)
		return (NULL);
	len = ft_str_arr_len(str_arr);
	result = add_malloc(len);
	if (!result)
		return (NULL);
	if (!add_copy(result, str_arr, len))
		return (NULL);
	if (!append_new_str(result, str, len))
		return (NULL);
	return (result);
}

char	**ft_str_arr_add(char **str_arr, char *new_str)
{
	char	**result;

	result = ft_str_arr_add_core((const char **)str_arr, (const char *)new_str);
	ft_str_arr_free(&str_arr);
	return (result);
}
