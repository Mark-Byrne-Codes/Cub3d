#include "../../include/cub3d.h"

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

int	return_error(t_game *game, char *msg)
{
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	if (game)
		free_map(game);
	if (game->map.fd >= 0)
	{
		free_gnl(game->map.fd);
		close(game->map.fd);
	}
	return (EXIT_FAILURE);
}

void	free_map(t_game *game)
{
	int	i;

	if (!game || !game->map.map_grid || !game->map.height)
		return ;
	i = 0;
	while (i < game->map.height)
	{
		if (game->map.map_grid[i])
			free(game->map.map_grid[i]);
		i++;
	}
	free(game->map.map_grid);
	game->map.map_grid = NULL;
}

int	get_height(t_game *game)
{
	char	*gnl;
	int		i;

	game->map.fd = open(game->map.file_path, O_RDONLY);
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

void	init_map_struct(t_game *game)
{
	game->map.fd = -1;
	game->map.width = 0;
	game->map.height = 0;
	game->map.start_dir = '\0';
	game->map.map_grid = NULL;
	game->map.file_path = NULL;
}

int	allocate_map_grid(t_game *game)
{
	int		i;
	char	*gnl;

	i = -1;
	gnl = get_next_line(game->map.fd);
	while (gnl != NULL && ++i < game->map.height)
	{
		game->map.width = ft_strlen(gnl);
		game->map.map_grid[i] = ft_calloc(game->map.width + 1, sizeof(char));
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
	init_map_struct(game);
	game->map.file_path = argv;
	game->map.height = get_height(game);
	if (game->map.height == -1)
		return (return_error(game, "Error:  Invalid map"));
	game->map.map_grid = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.map_grid)
		return (return_error(game, "Error: Failed to allocate map grid"));
	game->map.fd = open(game->map.file_path, O_RDONLY);
	if (game->map.fd == -1)
		return (return_error(game, "Error: Failed to open map file"));
	if (allocate_map_grid(game))
		return (return_error(game, "Error: Failed to allocate map row"));
	return (EXIT_SUCCESS);
}
// printf("height[%d]: && width: %d\n", i, game->map.width);