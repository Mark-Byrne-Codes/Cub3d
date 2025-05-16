#include "../../include/cub3d.h"

int flood_fill_in(char **map, int y, int x, int height, int width)
{
	if (y < 0 || y >= height || x < 0 || x >= width)
		return (0); // Out of bounds = invalid map (leak)
	if (map[y][x] == '1' || map[y][x] == 'V') // 'F' = already filled
		return (1);
	if (map[y][x] == ' ') // space = invalid area
		return (0);
	map[y][x] = 'V';
	if (!flood_fill_in(map, y + 1, x, height, width)
		|| !flood_fill_in(map, y - 1, x, height, width)
		|| !flood_fill_in(map, y, x + 1, height, width)
		|| !flood_fill_in(map, y, x - 1, height, width))
		return (0);
	return (1);
}

int flood_fill_out(char **map, int y, int x, int height, int width)
{
	if (y < 0 || y >= height || x < 0 || x >= width)
		return (0); // Out of bounds

	if (map[y][x] == '1' || map[y][x] == 'V' || map[y][x] == ' ')
		return (1); // Wall, already visited, or space = safe/ignored

	if (map[y][x] == '0' || ft_strchr("NSEW", map[y][x]))
		return (0); // Leak — reachable from outside

	map[y][x] = 'V'; // Mark as visited
	if (!flood_fill_out(map, y + 1, x, height, width)
		|| !flood_fill_out(map, y - 1, x, height, width)
		|| !flood_fill_out(map, y, x + 1, height, width)
		|| !flood_fill_out(map, y, x - 1, height, width))
		return (0);

	return (1);
}

int check_outer_map(t_game *game, char **map_copy)
{
	int		i;
	
	i = 0;
	while (i < game->map.max_width)  // Top and bottom rows
	{
		if (!flood_fill_out(map_copy, 0, i, game->map.height,game->map.max_width)
			|| !flood_fill_out(map_copy, game->map.height - 1, i, game->map.height,
			game->map.max_width))
			return (EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < game->map.height) // Left and right columns
	{
		if (!flood_fill_out(map_copy, i, 0, game->map.height, game->map.max_width)
			|| !flood_fill_out(map_copy, i, game->map.max_width - 1, game->map.height,
			game->map.max_width))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int check_map_walls(t_game *game)
{
	char	**map_copy;

	map_copy = duplicate_map(game);
	if (!map_copy)
		return (return_error(game, "Failed to copy map"));

	if (!flood_fill_in(map_copy, game->map.player_y, game->map.player_x,
		game->map.height, game->map.max_width))
		return (free_grid(map_copy), ERR_IN_MAP);
	if (check_outer_map(game, map_copy))
		return (free_grid(map_copy), ERR_OUT_MAP);
	free_grid(map_copy);
	printf("\033[1;32mMap enclosure validation successful!\033[0m\n");
	return (EXIT_SUCCESS);
}