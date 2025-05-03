#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include "./MLX42/MLX42.h"
# include "../libft/libft.h"

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_vec2 
{
    double  x;
    double  y;
}   t_vec2;

typedef struct s_ray
{

}   t_ray;

typedef struct s_player
{
    t_vec2 pos;
    t_vec2 dir;
    t_vec2 plane;
}   t_player;



typedef struct s_graphics
{
    mlx_image_t *north;
    mlx_image_t *south;
    mlx_image_t *west;
    mlx_image_t *east;
    int *c[3];
    int *f[3];
}  t_graphics;

typedef struct s_map
{
    char **map;
    int width;
    int height;
}   t_map;

typedef struct s_parser
{
// something like this for parsing
}   t_parser;

typedef struct s_game
{
    mlx_t *mlx;
    t_player *player;
    t_map    *map;
    t_ray   *ray;
    t_graphics *graphics;
    t_parser *parser;
}   t_game;


void    init_mlx(t_game *game);
void    run_game(t_game *game);
void    render_graphics(t_game *game);
void	control_player(mlx_key_data_t keydata, void *param);
void    clean_exit(t_game *game);
void	handle_esc(mlx_key_data_t keydata, t_game *game);

#endif