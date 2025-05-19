#ifndef DATA_H
# define DATA_H

# include "../minilibx_linux/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# ifndef KEYSYMS
#  define UP_KEY 0xff52
#  define DOWN_KEY 0xff54
#  define LEFT_KEY 0xff51
#  define RIGHT_KEY 0xff53
#  define W_KEY 0x77
#  define A_KEY 0x61
#  define S_KEY 0x73
#  define D_KEY 0x64
#  define Q_KEY 0x71
#  define ESC_KEY 0xff1b
#  define R_KEY 0x72
#  define G_KEY 0x67
#  define B_KEY 0x62
# endif

/* 
	ALLOWED EXTERNAL FUNCTIONS:
		open, close, read, write,
		printf, malloc, free, perror,
		strerror, exit, gettimeofday
	
		Anything in minilibx or math
*/





#endif
