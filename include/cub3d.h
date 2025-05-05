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
# define MAP_WIDTH 8
# define MAP_HEIGHT 8
# define PI 3.14159265358979323846


typedef struct s_ray
{
	double		x;
	double		y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	int			hit;
}				t_ray;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}   t_player;

typedef struct s_color
{
	int r;
	int g;
	int b;
}				t_color;

typedef struct s_graphics
{
    mlx_image_t north;
    mlx_image_t south;
    mlx_image_t west;
    mlx_image_t east;
	t_color		floor_color;
	t_color		ceiling_color;
}  t_graphics;

typedef struct s_map
{
    char **map;
    int width;
    int height;
    char start_dir;
    int			player_x;
	int			player_y;
}   t_map;

typedef struct s_parser
{
// something like this for parsing
}   t_parser;

typedef struct s_game
{
    mlx_t			*mlx;
	mlx_image_t		*img;
    void             *win;
    t_player player;
    t_map    map;
    t_ray   ray;
    t_graphics graphics;
    t_parser parser;
}   t_game;

int    init_game(t_game *game);
int   run_game(t_game *game);
void    render_graphics(void *param);
void	control_player(mlx_key_data_t keydata, void *param);
void    clean_exit(t_game *game);
void	handle_esc(mlx_key_data_t keydata, t_game *game);

#endif