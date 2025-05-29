/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:58:58 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/29 13:26:39 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "cube.h"


bool	error_msg(int fd, char *msg, char **cub);
bool	load_cub_file_contents(char ***cub, int fd);
bool	open_cub_file_and_copy_data(t_cube *data, char *filename);

bool	trim_first_six_lines(char **map);
bool	assign_texture_path(char *line, char *id, char **tex_path);
bool	chk_val(int color);
bool	assign_color_values(char *line, char *id, t_rgb *val);

bool	init_textures(t_tex *txs);
void	set_init_textures_paths_to_null(t_tex *txs);
bool	match_texture_path(char *line, t_tex *txs);
bool	validate_first_six_lines(char **map, t_tex *txs);

bool	parse_main(t_cube *data, char *filename);

#endif
