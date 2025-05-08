#include "../../include/cub3d.h"


int	main(int argc, char **argv)
{
	t_game	*game;
    static char *map[9] = {

        "11111111",
        
        "10000001",
        
        "10101001",
        
        "10000001",
        
        "10101001",
        
        "10000001",
        
        "10000001",
        
        "11111111",
        
        NULL
        
        };

	if (argc != 2 || !ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
	{
		ft_putstr_fd("Error\nPlease provide a .cub file.\n", 2);
		return (1);
	}
	game = malloc(sizeof(t_game));
	if (!game)
	{
		ft_putstr_fd("Error\nFailed to allocate memory for game.\n", 2);
		return (1);
	}
	// init_and_validate_map(argv[1]);
	game->map.map = map; // Placeholder for actual map loading
	game->map.width = 8;
	game->map.height = 8;
	if (run_game(game))
		clean_exit(game, "Error\nFailed to run game.\n");
	clean_exit(game, NULL);
	return (0);
}
