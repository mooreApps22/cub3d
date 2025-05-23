/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:52:12 by smoore            #+#    #+#             */
/*   Updated: 2025/05/23 17:23:14 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

unsigned int	get_color(t_image* asset, int x, int y)
{
	unsigned int	color;

	color = *(unsigned int*)(asset->addr + y
		* asset->line_len + x * (asset->bpp / 8));
	return (color);
}

char	*get_image_addr(t_image *asset)
{
	char *addr;

	addr = mlx_get_data_addr(asset->img,
		&asset->bpp, &asset->line_len, &asset->endian);
	if (!addr)
		return (NULL);
	return (addr);
}

void	blit_pixel_color(t_image *asset, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		*(unsigned int*)(asset->addr + y * asset->line_len
			+ x * (asset->bpp / 8)) = color;
}
