/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahamdan <hahamdan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:04:22 by hahamdan          #+#    #+#             */
/*   Updated: 2025/05/25 17:04:26 by hahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * Sets the palyer and its starting position on the map. 
 * @param game Game state struct that holds map data. 
 * @param i The starting index to search for the player in the map.
 * @return 'EXIT_SUCCESS' if the player is successufully set, or
 * an error code if failed.
 */
int	get_player_position(t_game *game, int i)
{
	int	j;
	int	found;

	found = 0;
	while (game->map.map_data[++i])
	{
		j = -1;
		while (game->map.map_data[i][++j])
		{
			if (!ft_strchr("01NSEW ", game->map.map_data[i][j]))
				return (INVALID_CHAR);
			if (ft_strchr("NSEW", game->map.map_data[i][j]))
			{
				found++;
				game->map.player_x = j;
				game->map.player_y = i;
				game->map.start_dir = game->map.map_data[i][j];
				if (found > 1)
					return (MULTI_PLAYER);
			}
		}
	}
	if (found == 0)
		return (NO_PLAYER);
	return (EXIT_SUCCESS);
}

static int	get_map_height(t_game *game, int i)
{
	int	height;

	height = 0;
	while (game->map.map_grid[i] != NULL)
	{
		i++;
		height++;
	}
	return (height);
}

static void	build_map_content(t_game *game, int start_index)
{
	int		i;
	int		j;
	char	*temp;

	i = start_index;
	j = -1;
	while (++j < game->map.height)
	{
		temp = ft_strtrim(game->map.map_grid[i], "\n");
		ft_memcpy(game->map.map_data[j], temp, ft_strlen(temp));
		free(temp);
		i++;
	}
}

static int	get_map_width(t_game *game, int start_index)
{
	int		i;
	char	*temp;

	i = start_index;
	while (game->map.map_grid[i] != NULL)
	{
		temp = ft_strtrim(game->map.map_grid[i], "\n");
		if (temp && !*temp)
			return (free(temp), EXIT_FAILURE);
		if ((int)ft_strlen(temp) > game->map.max_width)
			game->map.max_width = ft_strlen(temp);
		free(temp);
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * initialize an empty grid for the game map.
 * Allocates memory for the map and its rows, and initializes
 * each row with spaces.
 * @param game Game state struct that holds map data.
 * @param start_index Index where map data starts.
 * @return 'MAP_LINE' if theres empty line between map,
 * 'EXIT_SUCCESS if the map is successfully created, or an error code on failure
 */
int	init_map_grid(t_game *game, int start_index)
{
	int	j;

	if (get_map_width(game, start_index))
		return (MAP_LINE);
	game->map.height = get_map_height(game, start_index);
	if (game->map.height == 0)
		return (EMPTY_MAP);
	game->map.map_data = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.map_data)
		return (return_error(game, "Map allocation failed"));
	j = -1;
	while (++j < game->map.height)
	{
		game->map.map_data[j] = ft_calloc(game->map.max_width + 1,
				sizeof(char));
		if (!game->map.map_data[j])
			return (return_error(game, "Row allocation failed"));
		ft_memset(game->map.map_data[j], ' ', game->map.max_width);
		game->map.map_data[j][game->map.max_width] = '\0';
	}
	build_map_content(game, start_index);
	return (EXIT_SUCCESS);
}
