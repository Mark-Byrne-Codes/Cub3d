#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <string.h>
# include "./MLX42/MLX42.h"
# include "../libft/libft.h"

# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159265358979323846

# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.2
# define X_SIDE 0
# define Y_SIDE 1
# define WALL_HEIGHT_LIMIT 10000  


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_ray
{
    double  dir_x;
    double  dir_y;
    int     map_x;
    int     map_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  perp_wall_dist;
    int     step_x;
    int     step_y;
    int     hit;
    int     side;
    int     line_height;
    int     draw_start;
    int     draw_end;
    int     tex_x;
    double  tex_pos;
    double  step;
    // uint32_t color;
}   t_ray;

typedef enum e_wall_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_wall_dir;

// typedef enum e_error
// {
// 	ERR_FILE = 2,
// 	ERR_EXT,
// 	NO_EXT,
// 	ERR_DUP,
// 	ERR_IS_DIR,
// 	ERR_READ,
// 	INVALID_CHAR,
// 	MULTI_PLAYER,
// 	NO_PLAYER,
// 	NO_FILE,
// 	ERR_CONFIG,
// 	ERR_RGB,
// 	// NO_CONFIG,
// 	MAP_LINE,
// }				t_error;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
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
    mlx_image_t *north;
    mlx_image_t *south;
    mlx_image_t *west;
    mlx_image_t *east;
	t_color		floor_color;
	t_color		ceiling_color;
}				t_graphics;

typedef struct s_map
{
	int			fd;
	int			*widths;
	int			height;
	int 		max_width;
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
	ERR_IN_MAP,
	ERR_OUT_MAP,
	MAP_LINE,
}				t_error;


typedef struct s_game
{
    mlx_t			*mlx;
	mlx_image_t		*img;
    void             *win;
    t_player player;
    t_map    map;
    t_ray   ray;
    t_graphics graphics;
}   t_game;

int    init_game(t_game *game);
int   run_game(t_game *game);
void    render_graphics(void *param);
void	control_player(mlx_key_data_t keydata, void *param);
void    clean_exit(t_game *game, char *msg);
void	handle_esc(mlx_key_data_t keydata, t_game *game);
void 	raycast(t_game *game);
void	render_minimap(t_game *game);
int	load_textures(t_game *game);
mlx_image_t  *select_texture(t_game *game, t_ray *ray);
int  calculate_tex_x(t_ray *ray, mlx_image_t *tex, t_player *player);
void draw_vertical_line(t_game *game, int x, t_ray *ray, mlx_image_t *tex);
uint32_t create_rgba(t_color color);
int set_player_dir(t_game *game, char dir);
int				read_map(t_game *game, char *argv);
void			free_map(t_game *game);
int				validate_map_configuration(t_game *game);


int	handle_error(char *line, int err, char *element);
int	return_error(t_game *game, char *msg);

// int	validate_map_data(t_game *game, int i);
int check_map_walls(t_game *game);
char	**duplicate_map(t_game *game);
int handle_map_error(int err);
void	free_grid(char **split);
void	configuration_format(int err);
int	read_map(t_game *game, char *argv);
char	**trim_and_split(char *map_line);
int	load_config_element(t_game *game, char *element, char *line, char **arr);

int	create_empty_map(t_game *game, int start_index, int j);
int	check_map_element(char *element, char **arr);
int	create_empty_map(t_game *game, int start_index, int j);
void	free_gnl(int fd);
char	**duplicate_map(t_game *game);
int	check_duplication(t_game *game, const char *identifier);

// void    render_graphics(t_game *game);
// void	control_player(mlx_key_data_t keydata, void *param);
// void    clean_exit(t_game *game);
void	handle_esc(mlx_key_data_t keydata, t_game *game);


#endif

