/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:45:51 by mcoskune          #+#    #+#             */
/*   Updated: 2025/06/06 16:21:59 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../muk_lib.h"

/**
 * Frees a NULL-terminated array of pointers and the array itself.
 * The array must be NULL-terminated.
 * This function nullifies individual pointers after freeing.
 * Note that setting dptr = NULL has no effect since dptr is passed by value.
 * 
 * @param dptr The NULL-terminated array of pointers to free
 */
void	free_dptr(void **dptr)
{
	int	i;

	if (dptr == NULL)
		return ;
	i = 0;
	while (dptr[i] != NULL)
	{
		free(dptr[i]);
		dptr[i] = NULL;
		i++;
	}
	free(dptr);
}
