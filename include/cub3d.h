#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_vec2 
{
    double  x;
    double  y;
}   t_vec2;

typedef struct s_game
{

}   t_game;


typedef struct s_map
{
    char **map;
    int width;
    int height;
}   t_map;



#endif