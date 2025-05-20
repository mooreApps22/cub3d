/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:40:00 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/20 11:19:02 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/*~~~ Graphical Data ~~~*/
typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

/*~~~ MLX Window Manager Data ~~~*/
typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
}	t_mlx;

/*~~~ Map Data ~~~*/
typedef struct s_map
{
	char	**map;
}	t_map;

/*~~~ Texture Data ~~~*/
typedef struct s_tex
{
	char	*north_wall;
	char	*south_wall;
	char	*west_wall;
	char	*east_wall;
}	t_tex;

/*~~~ Player Data ~~~*/
typedef struct s_ply
{
	double	x_pos;
	double	y_pos;
	double	alpha;
}	t_ply;

/*~~~ Colour Data ~~~*/
typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}	t_rgb;

/*~~~ Main Data Structure ~~~*/
typedef struct s_cube
{
	t_mlx	mlx_data;
	t_map	map_data;
	t_tex	tex_data;
	t_ply	man_data;
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
