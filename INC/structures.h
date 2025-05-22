/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:40:00 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/22 11:49:16 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# ifndef HEIGHT
#  define HEIGHT 480
# endif

# ifndef WIDTH
#  define WIDTH 600
# endif

# ifndef TURN_RATE
#  define TURN_RATE 1
# endif

# ifndef MOVE_SPEED
#  define MOVE_SPEED 600
# endif

# ifndef TILE_SIZE_X
#  define TILE_SIZE_X 64
# endif

# ifndef TILE_SIZE_Y
#  define TILE_SIZE_Y 64
# endif

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
	double	alpha;	// Angle between 0 axis (North) and player character
	double	fov;	//Field of View (degrees)
}	t_ply;

/*~~~ Colour Data ~~~*/
typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}	t_rgb;

typedef struct s_tuple
{
	double	x;
	double	y;
	// double	z;
	// double	w;
}	t_tuple;

/*~~~ Texture Data ~~~*/
typedef struct s_tex
{
	char	*north_wall;
	char	*south_wall;
	char	*west_wall;
	char	*east_wall;
	t_rgb	*floor;
	t_rgb	*ceiling;
}	t_tex;

/*~~~ Main Data Structure ~~~*/
typedef struct s_cube
{
	t_mlx	mlx_data;
	t_image	image;
	t_map	map_data;
	t_tex	textures;
	t_ply	player;
	t_image	view; // image buffer for the player screen
	t_image	wall; //static scaled wall for test
	int		reset_frame; // signal for resetting the frame
}	t_cube;

typedef enum e_dir
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
	FLOOR = 4,
	CEILING,
	UNKNOWN
}	t_dir;


#endif
