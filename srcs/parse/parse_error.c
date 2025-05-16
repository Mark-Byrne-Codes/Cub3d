#include "../../include/cub3d.h"

int handle_map_error(int err)
{
	ft_putstr_fd("\033[1;31mError: Invalid map\033[0m\n", STDERR_FILENO);
	if (err == MULTI_PLAYER)
		ft_putstr_fd("Found multiple starting positions.\n"
		"The map must contain exactly one player (N, S, E or W).\n",
		STDERR_FILENO);
	else if (err == NO_PLAYER)
		ft_putstr_fd("Missing starting position.\n"
		"The map must contain exactly one player (N, S, E or W).\n",
		STDERR_FILENO);
	else if (err == INVALID_CHAR)
		ft_putstr_fd("Found invalid character.\n"
		"Allowed characters: 0, 1, N, S, W, E and space(s).\n",
		STDERR_FILENO);
	else if (err == ERR_IN_MAP)
		ft_putstr_fd("The map must be closed/surrounded by walls.\n",
		STDERR_FILENO);
	else if (err == ERR_OUT_MAP)
		ft_putstr_fd("Map borders must consist of solid walls (1) or space(s).\n",
		STDERR_FILENO);
	else if (err == MAP_LINE)
		ft_putstr_fd("Empty line(s) between map content.\n",
		STDERR_FILENO);
    return (EXIT_FAILURE);
}

int	handle_error(char *line, int err, char *element)
{
	ft_putstr_fd("\033[1;31mError: Invalid config\033[0m\n", STDERR_FILENO);
	if (err == ERR_EXT)
		ft_putstr_fd("Invalid texture format: Expected .png: ",
			STDERR_FILENO); 
	if (err == ERR_FILE)
		ft_putstr_fd("Cannot open file: ", STDERR_FILENO);
	if (err == ERR_CONFIG)
		return (ft_putstr_fd("Invalid map configuration\n", 2), 1); //check
	if (err == ERR_READ)
		ft_putstr_fd("Permission denied: Cannot read file: ", 2);
	if (err == NO_FILE)
		ft_putstr_fd("File does not exist: ", STDERR_FILENO);
	if (err == ERR_RGB || err == ERR_DUP || err == ERR_IS_DIR || err == NO_EXT)
	{
		if (err == ERR_RGB)
			ft_putstr_fd("Invalid color format: Expected R,G,B ([0-255]"
			" without spaces): ",
			STDERR_FILENO);
		else if (err == ERR_DUP)
			ft_putstr_fd("Duplicate map element definition: ", 2);
		else if (err == ERR_IS_DIR)
			ft_putstr_fd("Path is a directory: ", STDERR_FILENO);
		else
			ft_putstr_fd("Missing texture path for ", STDERR_FILENO);
		ft_putstr_fd(element, STDERR_FILENO);
		if (err == NO_EXT)
			ft_putstr_fd(" \n", STDERR_FILENO);
		else
			ft_putchar_fd(' ', STDERR_FILENO);
	}
	if (line)
		ft_putendl_fd(line, STDERR_FILENO);
	return (EXIT_FAILURE);
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

void	free_grid(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
}

void	free_map(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->map.map_grid)
	{
		i = -1;
		while (game->map.map_grid[++i])
			free(game->map.map_grid[i]);
		free(game->map.map_grid);
		game->map.map_grid = NULL;
	}
	if (game->map.map_data)
	{
		i = -1;
		while (game->map.map_data[++i])
			free(game->map.map_data[i]);
		free(game->map.map_data);
		game->map.map_data = NULL;
	}
	free(game->map.north_texture);
	free(game->map.south_texture);
	free(game->map.west_texture);
	free(game->map.east_texture);
	game->map.north_texture = NULL;
	game->map.south_texture = NULL;
	game->map.west_texture = NULL;
	game->map.east_texture = NULL;
	free(game->map.widths);
	game->map.widths = NULL;
	// free(game);
	// game = NULL;
}

