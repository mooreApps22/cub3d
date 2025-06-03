/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:36:32 by smoore            #+#    #+#             */
/*   Updated: 2025/06/03 15:20:39 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

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
# include <sys/time.h>

# include "structures.h"
# include "ft_str_arr_utils.h"
# include "parse.h"
# include "../LIB/LIBFT/libft.h"
# include "../LIB/muk_lib/muk_lib.h"

/*
	ALLOWED EXTERNAL FUNCTIONS:
	open, close, read, write, printf,
	malloc, free, perror, strerror,
	exit, gettimeofday
	Anything in minilibx or math
*/

/*~~~ CHECKS & INITIALIZATION ~~~*/
void			validate_input(int ac, char **av);
void			clean_initialize(t_cube *data);
void			init_mlx(t_cube *data);
/*~~~ KEY INPUTS ~~~*/
int				handle_keys(int keysys, t_cube *data);
int				handle_x_button(t_cube *data);
int				mouse_input(int x, int y, t_cube *data);

/*~~~ GAMEPLAY ~~~*/
double			tuple_magnitude(t_tuple tuple);
t_tuple			tuple_normalize(t_tuple tuple);
void			validate_movement(t_ply *player, t_tuple dir, t_map *level);
void			move_forward(t_cube *data);
void			move_left(t_cube *data);
void			move_back(t_cube *data);
void			move_right(t_cube *data);
void			turn_left(t_cube *data);
void			turn_right(t_cube *data);

/*~~~ RENDERING - VISUALS ~~~*/
void			iterate_down_image_buffer(t_image *buf, t_image *asset);
void			iterate_across_image_buffer(t_image *buf, t_tex *assets);
void			render_frame(t_cube *data, t_image *buf, t_tex *tx);

t_intersect		*ray_casting_main(t_cube *data);
double			normalize_angle(double alpha);

t_image			*get_wall_texture(t_tex *tx, int side);
void			paint_walls(t_cube *data, t_intersect *inter, int i);

/*~~~ RENDERING - UTILS ~~~*/
unsigned int	get_color(t_image *asset, int x, int y);
char			*get_image_addr(t_image *asset);
bool			load_texture(t_image *asset, void *mlx, char *path);
void			blit_pixel_color(t_image *asset, int x, int y, int color);
int				render_loop(t_cube *data);
int				render_timer(t_cube *data);
double			distance(t_tuple source, t_tuple destination);
double			normalize_angle(double alpha);
double			wall_height(t_intersect *inter, t_cube *data);

/*~~~ RAYS - VECTORS ~~~*/
t_tuple			find_forw_vector(t_cube *data);

/*~~~ CLEANUP ~~~*/
void			exit_cleanup(char *msg, t_cube *data, int exit_code);

/*~~~ DEBUG ~~~*/
void			print_player_data(t_cube *data);

#endif
