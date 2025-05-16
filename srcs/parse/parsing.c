#include "../../include/cub3d.h"

int	check_map_element(char *element, char **arr)
{
	if (ft_strcmp(element, "NO") != 0 && ft_strcmp(element, "SO") != 0
		&& ft_strcmp(element, "WE") != 0 && ft_strcmp(element, "EA") != 0
		&& ft_strcmp(element, "F") != 0 && ft_strcmp(element, "C") != 0)
	{
		if (element[0] == '1' || element[0] == '0' || element[0] == ' '
			|| element[0] == 'N' || element[0] == 'S' || element[0] == 'W'
			|| element[0] == 'E')
			return (MAP_LINE); // Special code for map lines
		return (ERR_CONFIG);
	}
	if (!arr[1])
		return (NO_EXT);
	if (arr[2])
		return (ERR_CONFIG);
	return (EXIT_SUCCESS);
}

void	configuration_format(int err)
{
	(void)err;
	ft_putstr_fd("\033[1;33mRequired configuration format:\033[0m\n",
		STDERR_FILENO);
	ft_putstr_fd("NO path/to/north_texture.png\n", STDERR_FILENO);
	ft_putstr_fd("SO path/to/south_texture.png\n", STDERR_FILENO);
	ft_putstr_fd("WE path/to/west_texture.png\n", STDERR_FILENO);
	ft_putstr_fd("EA path/to/east_texture.png\n", STDERR_FILENO);
	ft_putstr_fd("F  0,0,0  (RGB values 0-255)\n", STDERR_FILENO);
	ft_putstr_fd("C  0,0,0  (RGB values 0-255)\n", STDERR_FILENO);
}


int	check_required_config(t_game *game)

{
	if (!game->map.north_texture || !game->map.south_texture
		|| !game->map.west_texture || !game->map.east_texture
		|| !game->map.ceiling_set || !game->map.floor_set)
	{
		configuration_format(0);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}


int	find_player(t_game *game)
{
	int		i;
	int		j;
	char	c;
	int		found;

	// printf("\n\033[1;33m########## Player Validation ###############\033[0m\n");
	i = -1;
	found = 0;
	while (game->map.map_data[++i])
	{
		j = -1;
		while (game->map.map_data[i][++j])
		{
			c = game->map.map_data[i][j];
			if (!ft_strchr("01NSEW ", c))
				return (INVALID_CHAR);
			if (ft_strchr("NSEW", c))
			{
				found++;
				game->map.start_dir = c;
				game->map.player_x = j;
				game->map.player_y = i;
				if (found > 1)
					return (MULTI_PLAYER);
			}
		}
	}
	if (found == 0)
		return (NO_PLAYER);
	// printf("\033[1;32mPlayer validation successful!\033[0m\n");
	return (EXIT_SUCCESS);
}

int	validate_map_data(t_game *game, int i)
{
	int	err;

	err = create_empty_map(game, i, -1);
	if (err)
		return (handle_map_error(err));
	err = find_player(game);
	if (err)
		return (handle_map_error(err));
	err = check_map_walls(game);
	if (err)
		return (handle_map_error(err));
	return (EXIT_SUCCESS);
}
int	process_configuration(t_game *game, int i)
{
	char	**line;
  
	while (game->map.map_grid[++i] != NULL)
	{
		line = trim_and_split(game->map.map_grid[i]);
		if (!line)
		{
			if (errno == ENOMEM)
				return (EXIT_FAILURE);
			i++;
			continue ;

		}
		if (check_map_element(line[0], line) == MAP_LINE)
		{
			free_grid(line);
			break ;
		}
		if (load_config_element(game, line[0], line[1], line))
			return (free_grid(line), EXIT_FAILURE);

	}
	if (validate_map_data(game, i - 1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	validate_map_configuration(t_game *game)
{
	if (process_configuration(game, -1) == MAP_LINE)
		return (EXIT_FAILURE);
	// if (check_required_config(game))
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

