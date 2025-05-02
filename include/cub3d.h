#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_index
{
	int		i;
	int		j;
} t_index;

typedef struct s_map
{
	int		fd;
	int		max_width;
	int		max_height;
	char	*file_path;
	t_index	*index;
} t_map;


int run_game(argv);
#endif