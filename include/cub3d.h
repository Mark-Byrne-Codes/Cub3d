#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
// # include "./MLX42/MLX42.h"
# include "../libft/libft.h"

# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159265358979323846
# define EMPTY_LINE ((char **)1)

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
}				t_player;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_graphics
{
	// mlx_image_t north;
	// mlx_image_t south;
	// mlx_image_t west;
	// mlx_image_t east;
	t_color		floor_color;
	t_color		ceiling_color;
}				t_graphics;

typedef struct s_map
{
	int			fd;
	int			width;
	int			height;
	char		*file_path;
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

}				t_parser;

typedef enum e_error
{
	ERR_FILE = 2,
	ERR_EXT,
	NO_EXT,
	ERR_DUP,
	ERR_CONFIG,
	ERR_RGB,
	// NO_CONFIG,
	MAP_LINE,
}				t_error;

typedef struct s_game
{
	// mlx_t			*mlx;
	// mlx_window_t	*win;
	// mlx_image_t		*img;
	t_player	player;
	t_map		map;
	t_ray		ray;
	t_graphics	graphics;
	// t_parser parser;
}				t_game;

// void    init_mlx(t_game *game);
void			run_game(t_game *game);
int				read_map(t_game *game, char *argv);
void			free_map(t_game *game);
int				validate_map_configuration(t_game *game);
// void	free_gnl(int fd);

// void    render_graphics(t_game *game);
// void	control_player(mlx_key_data_t keydata, void *param);
// void    clean_exit(t_game *game);
// void	handle_esc(mlx_key_data_t keydata, t_game *game);

// int run_game(argv);
#endif



// int load_elements(t_game *game, char *element, char *line)
// {
// 	if (ft_strcmp(element, "NO") == 0)
// 		return (check_texture(game, line, "NO"));
// 	if (ft_strcmp(element, "SO") == 0 )
// 		return (check_texture(game, line, "SO"));
// 	if (ft_strcmp(element, "WE") == 0)
// 		return (check_texture(game, line, "WE"));
// 	if (ft_strcmp(element, "EA") == 0 )
// 		return (check_texture(game, line, "EAST"));
// 	if (ft_strcmp(element, "F") == 0 )
// 		return (check_color(game, line, 'F'));
// 	if (ft_strcmp(element, "C") == 0)
// 		return (check_color(game, line, 'C'));
// 	return (EXIT_SUCCESS);
// }

// int	validate_map(t_game *game)
// {
// 	int		i;
// 	char	**line;

// 	i = 0;
// 	while (game->map.map_grid[i] != NULL)
// 	{
// 		line = ft_split(game->map.map_grid[i], ' ');
// 		if (!line)
// 			return (EXIT_FAILURE);
// 		// if (!((ft_strcmp(line[0], "NO") == 0 || ft_strcmp(line[0], "SO") == 0
// 		// 	|| ft_strcmp(line[0], "WE") == 0 || ft_strcmp(line[0], "EA") == 0
// 		// 	|| ft_strcmp(line[0], "F") == 0 || ft_strcmp(line[0], "C") == 0)
// 		// 	&& line[1] && !line[2]))
// 			// return (EXIT_FAILURE);
// 		if (ft_strcmp(line[0], "NO") == 0)
// 		check_texture(game, line[1], "NO");
// 		if (ft_strcmp(line[0], "SO") == 0 )
// 		check_texture(game, line[1], "SO");
// 		if (ft_strcmp(line[0], "WE") == 0)
// 		check_texture(game, line[1], "WE");
// 		if (ft_strcmp(line[0], "EA") == 0 )
// 		check_texture(game, line[1], "EAST");
// 		if (ft_strcmp(line[0], "F") == 0 )
// 		check_color(game, line[1], 'F');
// 		if (ft_strcmp(line[0], "C") == 0)
// 		check_color(game, line[1], 'C');
// 		// if (load_elements(game, line[0], line[1]))
// 		// 	return (EXIT_FAILURE);
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }

// printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", 
// 	game->map.north_texture, game->map.south_texture,
// 	game->map.west_texture, game->map.east_texture);
// printf("C: %d, %d, %d\n", game->graphics.ceiling_color.r, 
// 	game->graphics.ceiling_color.g, game->graphics.ceiling_color.b);
// printf("F: %d, %d, %d\n", game->graphics.floor_color.r, 
// 	game->graphics.floor_color.g, game->graphics.floor_color.b);
// printf("here\n");
// printf("here\n");


