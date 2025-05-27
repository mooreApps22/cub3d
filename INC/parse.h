/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:58:58 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/27 15:26:06 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "cube.h"


bool	error_msg(int fd, char *msg, char **cub);
bool	load_cub_file_contents(char ***cub, int fd);
bool	open_cub_file_and_copy_data(t_cube *data, char *filename);

bool	parse_main(t_cube *data, char *filename);

#endif
