#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2 || !ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
	{
		ft_putstr_fd("Error\nPlease provide a .cub file.\n", 2);
		return (1);
	}
	game = malloc(sizeof(t_game));
	if (!game)
		clean_exit(NULL, "Failed to allocate memory for game");
	ft_memset(game, 0, sizeof(t_game));
	if (map_validation(game, argv[1]))
		clean_exit(game, NULL);
	if (run_game(game))
		clean_exit(game, "Failed to run game");
	clean_exit(game, NULL);
	return (0);
}
