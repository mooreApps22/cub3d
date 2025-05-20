/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:58:58 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/20 13:08:32 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "cube.h"

void	parse_main(t_cube *data, char *filename);
void	parse_textures(t_cube* data, int fd, char **line);
void	parse_map(t_cube *data, int fd, char **line);

#endif
