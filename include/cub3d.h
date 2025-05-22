#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "./MLX42/MLX42.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>

# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159265358979323846
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.2
# define X_SIDE 0
# define Y_SIDE 1
# define WALL_HEIGHT_LIMIT 10000
# define MAP_START 1
# define CONFIG_COUNT 6
# define CONFIG_ERROR -1

# ifndef O_DIRECTORY
#  define O_DIRECTORY 0200000
# endif


typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	double		tex_pos;
	double		step;
}				t_ray;

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
	mlx_image_t	*north;
	mlx_image_t	*south;
	mlx_image_t	*west;
	mlx_image_t	*east;
	t_color		floor_color;
	t_color		ceiling_color;
}				t_graphics;

typedef struct s_map
{
	int			count;
	int			fd;
	int			*widths;
	int			height;
	int			max_width;
	char		**map_grid;
	char		**map_data;
	char		start_dir;
	int			floor_set;
	int			ceiling_set;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
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
	EMPTY_MAP,
}				t_error;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	void		*win;
	t_player	player;
	t_map		map;
	t_ray		ray;
	t_graphics	graphics;
}				t_game;

int				init_game(t_game *game);
int				run_game(t_game *game);
void			render_graphics(void *param);
void			control_player(mlx_key_data_t keydata, void *param);
void			clean_exit(t_game *game, char *msg);
void			raycast(t_game *game);
mlx_image_t		*select_texture(t_game *game, t_ray *ray);
int				calculate_tex_x(t_ray *ray, mlx_image_t *tex, t_player *player);
void			draw_vertical_line(t_game *game, int x, t_ray *ray,
					mlx_image_t *tex);
mlx_image_t		*load_image(t_game *game, const char *path);
uint32_t		create_rgba(t_color color);
int				set_player_dir(t_game *game, char dir);


void			free_gnl(int fd);
void			free_grid(char **split);
int				convert_rgb(char *str);
void			free_map(t_game *game);
int 			ft_comma(char *str);
char			**duplicate_map(t_game *game);
int				map_error(int err);
char			**trim_and_split(char *map_line);;
int				return_error(t_game *game, char *msg);
int				read_map(t_game *game, char *argv);
int				map_validation(t_game *game, char *map_file);
int				get_player_position(t_game *game, int i);
void 			set_color(t_game *game, t_color rgb, char c);
int				config_error(char *line, int err, char *element);
int				validate_identifier(char *id, char **arr);
int				validate_map_layout(t_game *game);
int				init_map_grid(t_game *game, int map_start_index);
int				assign_element(t_game *game, char *element, char *line,
					char **arr);

#endif
