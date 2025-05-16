#include "../../include/cub3d.h"

void	init_map_struct(t_game *game)
{
	game->map.fd = -1;
	game->map.height = 0;
	game->map.max_width = 0;
	game->map.player_x = -1;
	game->map.player_y = -1;
	game->map.floor_set = 0;
	game->map.ceiling_set = 0;
	game->map.start_dir = '\0';
	game->map.widths = NULL;
	game->map.map_grid = NULL;
	game->map.map_data = NULL;
	game->map.north_texture = NULL;
	game->map.south_texture = NULL;
	game->map.west_texture = NULL;
	game->map.east_texture = NULL;
}

int	get_height(t_game *game, char *filename)
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

int	allocate_map_grid(t_game *game, int height)
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
	int	i;

	init_map_struct(game);
	height = get_height(game, argv);
	if (height == -1)
		return (return_error(game, "Error:  Invalid map"));
	game->map.map_grid = ft_calloc(height + 1, sizeof(char *));
	if (!game->map.map_grid)
		return (return_error(game, "Error: Failed to allocate map grid"));
	game->map.fd = open(argv, O_RDONLY);
	if (game->map.fd == -1)
		return (return_error(game, "Error: Failed to open map file"));
	if (allocate_map_grid(game, height))
		return (return_error(game, "Error: Failed to allocate map row"));
	i = 0;
	// printf("\033[1;33m########## Map file config ###############\033[0m\n");
	// while (i < height)
	// {
	// 	printf("%s", game->map.map_grid[i]);
	// 	i++;
	// }
	// printf("\n\n\033[1;33m##########ERROR###############\033[0m\n");
	close(game->map.fd);
	return (EXIT_SUCCESS);
}