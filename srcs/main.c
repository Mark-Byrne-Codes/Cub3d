#include "../../include/cub3d.h"

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
	{
		ft_putstr_fd("Error\nFailed to allocate memory for game.\n", 2);
		return (1);
	}
	// init_and_validate_map(argv[1]);
	// init_mlx();
	// init_game();
	// run_game();

	clean_exit(game);
	return (0);
}
