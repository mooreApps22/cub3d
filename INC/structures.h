/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:40:00 by mcoskune          #+#    #+#             */
/*   Updated: 2025/06/03 15:40:36 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# ifndef HEIGHT
#  define HEIGHT 500
# endif

# ifndef WIDTH
#  define WIDTH 640
# endif

# ifndef TURN_RATE
#  define TURN_RATE 1
# endif

# ifndef MOVE_SPEED
#  define MOVE_SPEED 600
# endif

# ifndef TILE_SIZE
#  define TILE_SIZE 64
# endif

typedef struct s_camera
{
	double	fov;
	double	turn_size;
	double	pp_size; // projection plane
	double	pp_x;
	double	pp_y;
	double	dist_to_pp;
	double	delta_fov;
}	t_camera;

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

/*~~~ Graphical Data ~~~*/
typedef struct s_image
{
	char			*path;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
	int				x; //
	int				y; //
	unsigned int	color;
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
	char			**data;
	unsigned short	height;
	unsigned short	width;
	int				map_line_start;
}	t_map;

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

/*~~~ Player Data ~~~*/
typedef struct s_ply
{
	// double	x_pos;
	// double	y_pos;
	t_tuple	pos;
	double	alpha;	// N: M_PI/2, E: 0, W: M_PI, S:-M_PI/2 
}	t_ply;

/*~~~ Texture Data ~~~*/
typedef struct s_tex
{
	t_image	*north_wall;
	t_image	*south_wall;
	t_image	*west_wall;
	t_image	*east_wall;
	t_rgb	*floor;
	t_rgb	*ceiling;
}	t_tex;

typedef struct s_intersect
{
	double	x;
	double	y;
	double	distance;
	t_dir	side;
}	t_intersect;

/*~~~ Wall Data Structure ~~~*/
typedef struct s_wall
{
	int		i;
	int		j;
	int		tex_x;
	int		tex_y;
	int		wall_h;
	int		draw_start;
	int		draw_end;
	double	step;
	double	tex_pos;
	t_image	*tex;
	char	*addr;
}	t_wall;

/*~~~ Wall Input Data Structure ~~~*/
typedef struct s_wall_input
{
	t_tex		*tx;
	t_image		*buf;
	t_intersect	*inter;
}	t_wall_input;

/*~~~ Player Info Structure ~~~*/
typedef struct s_player_info
{
	t_map	*map;
	t_ply	*player;
	int		*count;
}	t_player_info;

/*~~~ Main Data Structure ~~~*/
typedef struct s_cube
{
	t_mlx			mlx_data;
	t_image			image;
	t_map			map;
	t_tex			textures;
	t_ply			player;
	int				reset_frame; // signal for resetting the frame
	struct timeval	start;
	t_camera		cam;
}	t_cube;

#endif
