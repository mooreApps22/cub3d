#ifndef DATA_H
# define DATA_H

# include "../LIB/minilibx-linux/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

# include <errno.h>
# include <X11/keysym.h>
#include <sys/time.h>

# include "structures.h"
# include "ft_str_arr_utils.h"
# include "parse.h"
# include "../LIB/LIBFT/libft.h"
# include "../LIB/muk_lib/muk_lib.h"

/* 
	ALLOWED EXTERNAL FUNCTIONS:
		open, close, read, write,
		printf, malloc, free, perror,
		strerror, exit, gettimeofday
	
		Anything in minilibx or math
*/

/*~~~ CHECKS & INITIALIZATION ~~~*/
void	validate_input(int ac, char **av);
void	clean_initialize(t_cube *data);
void	init_mlx(t_cube *data);


/*~~~ KEY INPUTS ~~~*/
int		handle_keys(int keysys, t_cube *data);
int		handle_x_button(t_cube *data);

/*~~~ GAMEPLAY ~~~*/
void	move_forward(t_cube *data);
void	move_left(t_cube *data);
void	move_back(t_cube *data);
void	move_right(t_cube *data);
void	turn_left(t_cube *data);
void	turn_right(t_cube *data);

/*~~~ RENDERING - VISUALS ~~~*/
void	iterate_down_image_buffer(t_image *buf, t_image *asset);
void	iterate_across_image_buffer(t_image *buf, t_tex *assets);
void	render_frame(t_cube *data, t_image *buf, t_tex *tx);

t_intersect	*ray_casting_main(t_cube *data);
double		normalize_angle(double alpha);


/*~~~ RENDERING - UTILS ~~~*/
unsigned int	get_color(t_image* asset, int x, int y);
char			*get_image_addr(t_image *asset);
void			blit_pixel_color(t_image *asset, int x, int y, int color);
int				render_loop(t_cube *data);
int				render_timer(t_cube *data);


/*~~~ RENDERING - GET_ASSETS ~~~*/
t_image			*get_asset(t_tex *assets);

/*~~~ RAYS - VECTORS ~~~*/
t_tuple	find_forw_vector(t_cube *data);

/*~~~ CLEANUP ~~~*/
void	exit_cleanup(char *msg, t_cube *data, int exit_code);




#endif
