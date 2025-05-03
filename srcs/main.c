int	main(int argc, char **argv)
{
	if (argc != 2 || !ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
	{
		ft_putstr_fd("Error\nPlease provide a .cub file.\n", 2);
		return (1);
	}
	// init_and_validate_map(argv[1]);
	// init_mlx();
	// init_game();


	return (0);
}
