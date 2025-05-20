/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:40:00 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/20 19:19:26 by smoore           ###   ########.fr       */
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
	int		width;
	int		height;
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

/*~~~ Player Data ~~~*/
typedef struct s_ply
{
	double	x_pos;
	double	y_pos;
	double	alpha; // 0 deg is north
	double	fov;
}	t_ply;

/*~~~ Colour Data ~~~*/
typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}	t_rgb;

/*~~~ Texture Data ~~~*/
typedef struct s_tex
{
	char	*north_wall;
	char	*south_wall;
	char	*west_wall;
	char	*east_wall;
	t_rgb	*floor;
	t_rgb	*ground;
}	t_tex;

/*~~~ Main Data Structure ~~~*/
typedef struct s_cube
{
	t_mlx	mlx_data;
	t_map	map_data;
	t_tex	textures;
	t_ply	player;
	t_image	view; // image buffer for the player screen
	t_image	wall; //static scaled wall for test
	int		reset_frame; // signal for resetting the frame
}	t_cube;

typedef enum e_dir
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING
} t_dir;


#endif
