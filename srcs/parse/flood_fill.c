#include "../../include/cub3d.h"

int	flood_fill_in(char **map, int y, int x, t_game *game)
{
	if (y < 0 || y >= game->map.height || x < 0
		|| x >= game->map.max_width)
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (1);
	if (map[y][x] == ' ')
		return (0);
	map[y][x] = 'V';
	if (!flood_fill_in(map, y + 1, x, game)
		|| !flood_fill_in(map, y - 1, x, game)
		|| !flood_fill_in(map, y, x + 1, game)
		|| !flood_fill_in(map, y, x - 1, game))
		return (0);
	return (1);
}

int	flood_fill_out(char **map, int y, int x, t_game *game)
{
	if (y < 0 || y >= game->map.height || x < 0
		|| x >= game->map.max_width)
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V' || map[y][x] == ' ')
		return (1);
	if (map[y][x] == '0' || ft_strchr("NSEW", map[y][x]))
		return (0);
	map[y][x] = 'V';
	if (!flood_fill_out(map, y + 1, x, game)
		|| !flood_fill_out(map, y - 1, x, game)
		|| !flood_fill_out(map, y, x + 1, game)
		|| !flood_fill_out(map, y, x - 1, game))
		return (0);
	return (1);
}

/**
 * Checks the outer bounderies of the map to detect
 * potential leaks. Performs a flood-fill starting from the outer edges
 * (top row, bottom row, left column, right column) that ensure no
 * accessible tiles ('0' or player start positions) are reachable from
 * outside the enclosed area of the map.
 * @param game Game state struct that holds map data.
 * @param map_copy A copied version of the map. 
 * @return returns 'EXIT_FAILURE' if runs into walkable or invalid space,
 * Otherwise returns 'EXIT_SUCCESS'.
 */
int	check_outer_map(t_game *game, char **map_copy)
{
	int	i;

	i = 0;
	while (i < game->map.max_width)
	{
		if (!flood_fill_out(map_copy, 0, i, game)
			|| !flood_fill_out(map_copy, game->map.height - 1, i, game))
			return (EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < game->map.height)
	{
		if (!flood_fill_out(map_copy, i, 0, game)
			|| !flood_fill_out(map_copy, i, game->map.max_width - 1, game))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * Checks wether all'0' and player starting position in the map are
 * properly enclosed.
 * @param map A 2D grid of characters (copied version).
 * @param height Numbers of rows in the map. 
 * @param width Numbers of columns in thr map.
 * @return returns 0 if a '0' character or player tile touches the edge
 * of the map or is next to a space, returns 1 If everything is safely
 * enclosed.
 */
int	validate_zero_neighbors(char **map, int height, int width)
{
	int	y;
	int	x;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			if (map[y][x] == '0' || ft_strchr("NSEW", map[y][x]))
			{
				if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
					return (0);
				if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' ||
					map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
					return (0);
			}
		}
	}
	return (1);
}

/**
 * Validates the map layout by performing flood-fill
 * algorithm that checks the validity of paths and the 
 * enclosure of the map.
 * @param game Game state struct that holds map data.
 * @return If any of these checks fail, it returns an
 * error code. Otherwise, returns EXIT_SUCCESS.
 */
int	validate_map_layout(t_game *game)
{
	char	**map_copy;

	map_copy = duplicate_map(game);
	if (!map_copy)
		return (return_error(game, "Failed to copy map"));
	if (!flood_fill_in(map_copy, game->map.player_y,
			game->map.player_x, game))
		return (free_grid(map_copy), ERR_IN_MAP);
	if (check_outer_map(game, map_copy))
		return (free_grid(map_copy), ERR_OUT_MAP);
	if (!validate_zero_neighbors(map_copy, game->map.height,
			game->map.max_width))
		return (free_grid(map_copy), ERR_OUT_MAP);
	free_grid(map_copy);
	printf("\033[1;32mMap enclosure validation successful!\033[0m\n");
	return (EXIT_SUCCESS);
}
