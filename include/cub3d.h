#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include "./MLX42/MLX42.h"
# include "../libft/libft.h"

# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159265358979323846

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

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
}				t_player;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_graphics
{
	mlx_image_t north;
	mlx_image_t south;
	mlx_image_t west;
	mlx_image_t east;
	t_color		floor_color;
	t_color		ceiling_color;
}				t_graphics;

typedef struct s_map
{
	int			fd;
	int			width;
	int			height;
	// char		*file_path;
	char		**map_grid;
	char 		**map_data;
	char		start_dir;
	int 		floor_set;
	int 		ceiling_set;
	char 		*north_texture;
	char 		*south_texture;
	char 		*west_texture;
	char 		*east_texture;
	int			player_x;
	int			player_y;
}				t_map;


typedef enum e_error
{
	ERR_FILE = 2,
	ERR_EXT,
	NO_EXT,
	ERR_DUP,
	ERR_IS_DIR,
	ERR_READ,
	INVALID_CHAR,
	MULTI_PLAYER,
	NO_PLAYER,
	NO_FILE,
	ERR_CONFIG,
	ERR_RGB,
	// NO_CONFIG,
	MAP_LINE,
}				t_error;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_window_t	*win;
	mlx_image_t		*img;
	t_player	player;
	t_map		map;
	t_ray		ray;
	t_graphics	graphics;
}				t_game;

void    		init_mlx(t_game *game);
void			run_game(t_game *game);
int				read_map(t_game *game, char *argv);
void			free_map(t_game *game);
int				validate_map_configuration(t_game *game);

// void    render_graphics(t_game *game);
// void	control_player(mlx_key_data_t keydata, void *param);
// void    clean_exit(t_game *game);
// void	handle_esc(mlx_key_data_t keydata, t_game *game);

// int run_game(argv);
#endif
