#include "../../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2 || !ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
	{
		ft_putstr_fd("Error\nPlease provide a .cub file.\n", 2);
		return (1);
	}
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		ft_putstr_fd("Error\nFailed to allocate memory for game.\n", 2);
		return (1);
	}
	if (read_map(game, argv[1]) == EXIT_FAILURE)
		free_map(game);
	if (validate_map(game))
	{
		free_map(game);
		printf("Error: Invalid map\n");
		// exit(1);
	}
	printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", 
		game->map.north_texture, game->map.south_texture,
		game->map.west_texture, game->map.east_texture);
	printf("C: %d, %d, %d\n", game->graphics.ceiling_color.r, 
		game->graphics.ceiling_color.g, game->graphics.ceiling_color.b);
	printf("F: %d, %d, %d\n", game->graphics.floor_color.r, 
		game->graphics.floor_color.g, game->graphics.floor_color.b);
	if (game->map.ceiling_set == 0)
		printf("not set\n");
	
	// init_and_validate_map(argv[1]);
	// init_mlx();
	// init_game();
	// run_game(g);

	// clean_exit(game);
	
	if (game)
		free_map(game);
	free(game);
	// // free_gnl(game->map.fd);
	return (0);
}
