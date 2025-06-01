/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:52:12 by smoore            #+#    #+#             */
/*   Updated: 2025/06/01 12:49:00 by smoore           ###   ########.fr       */
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

bool	load_texture(t_image *asset, void *mlx, char *path)
{
	if (!mlx)
		return (error_msg(0, "No mlx argument in load texture.", NULL));
	if (!path)
		return (error_msg(0, "No path argument in load texture.", NULL));
	printf("attempting mlx_xpm_file_to_image() for %s\n", path);
	asset->img = mlx_xpm_file_to_image(mlx, path, &asset->width, &asset->height);
	if (!asset->img)
		return (error_msg(0, "Failed to get img pointer from textures.", NULL));
	asset->addr = get_image_addr(asset); 
	if (!asset->addr)
		return (error_msg(0, "Failed to get addr data from textures.", NULL));
	return (true);
}

void	blit_pixel_color(t_image *asset, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		*(unsigned int*)(asset->addr + y * asset->line_len
			+ x * (asset->bpp / 8)) = color;
}
