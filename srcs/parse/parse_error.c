#include "../../include/cub3d.h"

/**
 * writes an error message based on the provided error code.
 * @param err An error code.
 * @return 'EXIT_FAILURE' to signal an error.
 */
int handle_map_error(int err)
{
	ft_putstr_fd("\033[1;31mError\033[0m\n", STDERR_FILENO);
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
		ft_putstr_fd("Map must be closed/surrounded by walls.\n",
		STDERR_FILENO);
	else if (err == ERR_OUT_MAP)
		ft_putstr_fd("Map must be completely surrounded by solid walls.\n",
		STDERR_FILENO);
	else if (err == MAP_LINE)
		ft_putstr_fd("Empty line(s) between map content.\n",
		STDERR_FILENO);
	else if (err == EMPTY_MAP)
			ft_putstr_fd("Missing map content.\n", STDERR_FILENO);
    return (EXIT_FAILURE);
}

/**
 * Writes an error message based on the provided error code.
 * @param line A line from the configuration (if applicable).
 * @param err An error code.
 * @param element The name of the element involved in the error.
 * @return 'EXIT_FAILURE' to signal an error.
 */
int	handle_config_error(char *line, int err, char *element)
{
	ft_putstr_fd("\033[1;31mError\033[0m\n", STDERR_FILENO);
	if (err == ERR_EXT)
		ft_putstr_fd("Invalid texture format: Expected .png: ",
			STDERR_FILENO); 
	if (err == ERR_FILE)
		ft_putstr_fd("Cannot open file: ", STDERR_FILENO);
	if (err == ERR_READ)
		ft_putstr_fd("Permission denied: Cannot read file: ", 2);
	if (err == NO_FILE)
		ft_putstr_fd("File does not exist: ", STDERR_FILENO);
	if (err == ERR_RGB || err == ERR_DUP || err == ERR_IS_DIR)
	{
		if (err == ERR_RGB)
			ft_putstr_fd("Invalid color value(s): ",
			STDERR_FILENO);
		else if (err == ERR_DUP)
			ft_putstr_fd("Found duplicate element definition: ", 2);
		else if (err == ERR_IS_DIR)
			ft_putstr_fd("Texture path is a directory: ", STDERR_FILENO);
		ft_putstr_fd(element, STDERR_FILENO);
		ft_putchar_fd(' ', STDERR_FILENO);
	}
	if (line)
		ft_putendl_fd(line, STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	return_error(t_game *game, char *msg)
{
	if (msg)
	{
		ft_putstr_fd("\033[1;31mError\033[0m\n",
		STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
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
	if (!game)
		return ;
	if (game->map.map_grid)
		free_grid(game->map.map_grid);
	if (game->map.map_data)
		free_grid(game->map.map_data);
	free(game->map.north_texture);
	free(game->map.south_texture);
	free(game->map.west_texture);
	free(game->map.east_texture);
	game->map.north_texture = NULL;
	game->map.south_texture = NULL;
	game->map.west_texture = NULL;
	game->map.east_texture = NULL;
}
