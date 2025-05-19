/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:40:00 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/19 19:12:14 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_image
{
	
}	t_image;

typedef struct s_mlx
{
	/* data */
}	t_mlx;


typedef struct s_cube
{
}	t_cube;

typedef enum e_
{
	NORTH = 0,	
	SOUTH = 1,	
	WEST = 2,
	EAST = 3,
	FLOOR = 4,
	CEILING = 5
} t_;

typedef struct s_textures
{
	int		fd;
	char*	north_path;
	char*	south_path;
	char*	east_path;
	char*	west_path;
	bool	no_found;
	bool	so_found;
	bool	ea_found;
	bool	we_found;
	bool	floor_found;
	bool	ceiling_found;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
}	t_textures;


#endif
