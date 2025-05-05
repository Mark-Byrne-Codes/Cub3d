#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
// # include "./MLX42/MLX42.h"
# include "../libft/libft.h"

# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159265358979323846

// # ifndef BUFFER_SIZE
// #  define BUFFER_SIZE 1024
// # endif

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
    // mlx_image_t north;
    // mlx_image_t south;
    // mlx_image_t west;
    // mlx_image_t east;
	t_color		floor_color;
	t_color		ceiling_color;
}  t_graphics;

typedef struct s_map
{
	int 	fd;
	char *file_path;
    char **map_grid;
    int width;
    int height;
    char start_dir;
    int			player_x;
	int			player_y;
}   t_map;

typedef struct s_parser
{
	// char 	**map_grid;
	// int 	width;
	// int 	height;
	// int 	start_pos;
	// t_graphics s_graphics;
	// t_map 	map;
	// int 	fd;
	// char 	*file_path;

}   t_parser;

typedef enum e_attribute
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING
} t_attribute;

typedef struct s_game
{
    // mlx_t			*mlx;
	// mlx_window_t	*win;
	// mlx_image_t		*img;
    t_player player;
    t_map    map;
    t_ray   ray;
    t_graphics graphics;
    t_parser parser;
}   t_game;


void    init_mlx(t_game *game);
void    run_game(t_game *game);
int read_map(t_game *game, char *argv);
void 	free_map(t_game *game);
// void	free_gnl(int fd);

// void    render_graphics(t_game *game);
// void	control_player(mlx_key_data_t keydata, void *param);
// void    clean_exit(t_game *game);
// void	handle_esc(mlx_key_data_t keydata, t_game *game);

// int run_game(argv);
#endif