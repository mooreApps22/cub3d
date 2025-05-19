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

# include "structures.h"
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

void	validate_input(int ac, char **av);
void	exit_cleanup(char *msg, t_cube *data, int exit_code);




#endif
