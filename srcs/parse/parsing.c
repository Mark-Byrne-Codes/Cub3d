/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahamdan <hahamdan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:03:56 by hahamdan          #+#    #+#             */
/*   Updated: 2025/05/25 17:04:00 by hahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * Validates the identifier in the map configuration line.
 * @param id The element identifier.
 * @param arr A line contains the element and its value.
 * @return 'MAP_START' if the line contains map data,
 * 'EXIT_FAILURE' if there's an invalid identifier, or
 * 'EXIR_SUCCESS' if the identifier is valid and well-formed.
 */
int	validate_identifier(char *id, char **arr)
{
	if (ft_strcmp(id, "NO") != 0
		&&ft_strcmp(id, "F") != 0
		&& ft_strcmp(id, "C") != 0
		&& ft_strcmp(id, "SO") != 0
		&& ft_strcmp(id, "WE") != 0
		&& ft_strcmp(id, "EA") != 0)
	{
		if (id[0] == '1' || id[0] == '0'
			|| id[0] == ' ' || id[0] == 'N'
			|| id[0] == 'S' || id[0] == 'W'
			|| id[0] == 'E')
			return (MAP_LINE);
		return (EXIT_FAILURE);
	}
	if (!arr[1] || arr[2])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * Handles configuration line in the map.
 * @param game Game state structure.
 * @param line A line from the map.
 * @param count Counts the current number of valid configuration lines.
 * @return 'MAP_START' if the line contains map data
 * and all line configurations are set,
 * 'CONFIG_ERROR' if there's an invalid configuration, or
 * 'EXIT_SUCCESS if not all configurations are set yet.
 */
static int	config_handler(t_game *game, char **line, int *count)
{
	int	result;

	result = validate_identifier(line[0], line);
	if (result == MAP_LINE)
	{
		if (*count == CONFIG_COUNT)
			return (free_grid(line), MAP_START);
		ft_putstr_fd("\033[1;31mError\033[0m\n"
			"Invalid map configuration.\n", 2);
		return (free_grid(line), CONFIG_ERROR);
	}
	if (result != EXIT_SUCCESS)
	{
		ft_putstr_fd("\033[1;31mError\033[0m\n"
			"Invalid map configuration.\n", 2);
		return (free_grid(line), CONFIG_ERROR);
	}
	if (assign_element(game, line[0], line[1], line))
		return (free_grid(line), CONFIG_ERROR);
	(*count)++;
	free_grid(line);
	return (EXIT_SUCCESS);
}

/**
 * Validates the game map
 * @param Game state struct.
 * @param start_index The index where the map data starts.
 * @return 'EXIT_SUCCESS' if validation passed, or
 * 'EXIT_FAILURE if validation failed.
 */
static int	validate_game_map(t_game *game, int start_index)
{
	int	err;

	err = init_map_grid(game, start_index);
	if (err)
		return (map_error(err));
	err = get_player_position(game, -1);
	if (err)
		return (map_error(err));
	err = validate_map_layout(game);
	if (err)
		return (map_error(err));
	return (EXIT_SUCCESS);
}

/**
 *  * Parses map configuration lines until the map data is encounterd.
 * @param game Game state structure.
 * @return 
 * Index where map data starts, or -1 on error.
 */
static int	parse_map_config(t_game *game)
{
	char	**line;
	int		count;
	int		status;
	int		current_index;

	count = 0;
	current_index = 0;
	while (game->map.map_grid[current_index] != NULL)
	{
		line = trim_and_split(game->map.map_grid[current_index]);
		if (!line)
		{
			current_index++;
			continue ;
		}
		status = config_handler(game, line, &count);
		if (status == MAP_START)
			break ;
		if (status == CONFIG_ERROR)
			return (CONFIG_ERROR);
		current_index++;
	}
	return (current_index);
}

/**
 * Validates the map and its congiguration.
 * @param game Game state struct.
 * @param map_file The path to the map file.
 * @return 'EXIT_SUCCESS' if validation passed, or
 * 'EXIT_FAILURE if validation failed.
 */
int	map_validation(t_game *game, char *map_file)
{
	int	map_start_index;

	if (read_map(game, map_file))
		return (EXIT_FAILURE);
	map_start_index = parse_map_config(game);
	if (map_start_index == CONFIG_ERROR)
		return (EXIT_FAILURE);
	if (validate_game_map(game, map_start_index))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
