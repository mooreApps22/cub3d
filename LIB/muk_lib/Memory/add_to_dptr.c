/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_dptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:00:30 by mcoskune          #+#    #+#             */
/*   Updated: 2025/06/06 16:21:23 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../muk_lib.h"
#include "../../../INC/cube.h"

static void	copy_dptr(void ***old_dptr, void **new_dptr, void *to_add)
{
	int	i;

	i = 0;
	while ((*old_dptr)[i] != NULL)
	{
		new_dptr[i] = (*old_dptr)[i];
		i++;
	}
	new_dptr[i] = to_add;
	new_dptr[i + 1] = NULL;
	if (old_dptr && *old_dptr)
		free(*old_dptr);
	*old_dptr = new_dptr;
}

int	add_to_dptr(void ***dptr, void *to_add)
{
	int		i;
	void	**new_dptr;

	i = 0;
	if (dptr == NULL || to_add == NULL)
		return (1);
	if (*dptr == NULL)
	{
		*dptr = (void **)malloc(sizeof(void *) * 2);
		if (*dptr == NULL)
			return (2);
		(*dptr)[0] = to_add;
		(*dptr)[1] = NULL;
	}
	else
	{
		while ((*dptr)[i] != NULL)
			i++;
		new_dptr = (void **)malloc(sizeof(void *) * (i + 2));
		if (new_dptr == NULL)
			return (2);
		copy_dptr(dptr, new_dptr, to_add);
	}
	return (0);
}

int	add_to_ptr(void **ptr, void *to_add)
{
	if (ptr == NULL || to_add == NULL)
		return (1);
	*ptr = to_add;
	return (0);
}
