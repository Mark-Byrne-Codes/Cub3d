#include "../../include/cub3d.h"

static void	init_map_struct(t_game *game)
{
	game->map.fd = -1;
	game->map.height = 0;
	game->map.max_width = 0;
	game->map.player_x = -1;
	game->map.player_y = -1;
	game->map.floor_set = false;
	game->map.ceiling_set = false;
	game->map.start_dir = '\0';
	game->map.map_grid = NULL;
	game->map.map_data = NULL;
	game->map.north_texture = NULL;
	game->map.south_texture = NULL;
	game->map.west_texture = NULL;
	game->map.east_texture = NULL;
}

void	free_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

static int	get_height(t_game *game, char *filename)
{
	char	*gnl;
	int		i;

	game->map.fd = open(filename, O_RDONLY);
	if (game->map.fd == -1)
		return (-1);
	gnl = get_next_line(game->map.fd);
	if (!gnl)
		return (-1);
	i = 0;
	while (gnl != NULL && *gnl != '\0')
	{
		i++;
		free(gnl);
		gnl = get_next_line(game->map.fd);
	}
	if (i <= 0)
		return (-1);
	close(game->map.fd);
	return (i);
}

static int	allocate_map_grid(t_game *game, int height)
{
	int		i;
	char	*gnl;

	i = -1;
	gnl = get_next_line(game->map.fd);
	if (!gnl)
		return (EXIT_FAILURE);
	while (gnl && ++i < height)
	{
		game->map.map_grid[i] = ft_strdup(gnl);
		if (!game->map.map_grid[i])
			return (free(gnl), EXIT_FAILURE);
		free(gnl);
		gnl = get_next_line(game->map.fd);
	}
	if (gnl)
		free(gnl);
	return (EXIT_SUCCESS);
}

int	read_map(t_game *game, char *argv)
{
	int	height;

	init_map_struct(game);
	height = get_height(game, argv);
	if (height == -1)
		return (return_error(game, "Empty file."));
	game->map.map_grid = ft_calloc(height + 1, sizeof(char *));
	if (!game->map.map_grid)
		return (return_error(game, "Failed to allocate map grid."));
	game->map.fd = open(argv, O_RDONLY);
	if (game->map.fd == -1)
		return (return_error(game, "Failed to open map file."));
	if (allocate_map_grid(game, height))
		return (return_error(game, "Failed to allocate map."));
	close(game->map.fd);
	return (EXIT_SUCCESS);
}
