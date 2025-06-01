/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:13:43 by smoore            #+#    #+#             */
/*   Updated: 2025/06/01 14:00:27 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	load_all_textures(t_tex *txs, void *mlx)
{	
	if (!mlx)
		return (error_msg(0, "No mlx passed into load all textures.", NULL));
	printf("Post load_all_textures pass: %p\n", mlx);
	printf("Path North: %s\n", txs->north_wall->path);
	if (!load_texture(txs->north_wall, mlx, txs->north_wall->path))
		return (error_msg(0, "Failed get north_wall addr.", NULL));
	if (!load_texture(txs->south_wall, mlx, txs->south_wall->path))
		return (error_msg(0, "Failed get south_wall addr.", NULL));
	if (!load_texture(txs->east_wall, mlx, txs->east_wall->path))
		return (error_msg(0, "Failed get east_wall addr.", NULL));
	if (!load_texture(txs->west_wall, mlx, txs->west_wall->path))
		return (error_msg(0, "Failed get west_wall addr.", NULL));
	return (true);
}

bool	validate_cub_data(t_map *map, t_tex *txs, t_ply *player, void *mlx)
{
	if (!map)
		return (error_msg(0, "No map to validate.", NULL));
	if (!trim_first_six_lines(map->data))
		return (error_msg(0, "Failed to trim first six lines.", NULL));
	if (!validate_first_six_lines(map->data, txs, &map->map_line_start))
		return (error_msg(0, "Failed to validate 1st six lines.", NULL));
	if (!extract_remaining_lines(map, txs))
		return (error_msg(0, "Failed to extract lines.", NULL));
	if (!validate_map_lines(map))
		return (error_msg(0, "Failed to validate map lines.", NULL));
	if (!validate_floor_tiles_are_enclosed(map))
		return (error_msg(0, "Failed to validate floor tiles.", NULL));
	if (!validate_player(map, player))
		return (error_msg(0, "Failed to validate player.", NULL));
	if (!validate_map_dimensions(map))
		return (error_msg(0, "Failed to validate map dimensions.", NULL));
	if (!validate_xpm_extensions(txs))
		return (error_msg(0, "Failed to validate .xpm extensions.", NULL));
	printf("Pre load_all_textures pass: %p\n", mlx);
	if (!load_all_textures(txs, mlx))
		return (error_msg(0, "Failed to load all textures.", NULL));
	return (true);	
}

bool	parse_main(t_cube *data, char *filename)
{
	ft_printf("mlx ptr: %p\n", data->mlx_data.mlx_ptr);
	if (!open_cub_file_and_copy_data(data, filename))
		return (error_msg(0, "failed to extract cub file data.", NULL));
	if (!validate_cub_data(&data->map, &data->textures, &data->player,
		data->mlx_data.mlx_ptr))
		return (error_msg(0, "failed to validate cub data.", NULL));
	return (true);
}
