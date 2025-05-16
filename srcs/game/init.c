#include "../../include/cub3d.h"

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!game->mlx)
	{
		ft_putstr_fd("Error\nFailed to initialize MLX\n", 2);
		return (1);
	}
	game->win = game->mlx->window;
	if (!game->win)
	{
		ft_putstr_fd("Error\nFailed to get window\n", 2);
		mlx_terminate(game->mlx);
		return (1);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		mlx_terminate(game->mlx);
		ft_putstr_fd("Error\nFailed to create image\n", 2);
		return (1);
	}
	return (0);
}

int	init_player(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0;
	return (0);
}

int	init_game(t_game *game)
{
	if (init_player(game))
		return (1);
	set_player_dir(game, game->map.start_dir);
	if (init_mlx(game))
		return (1);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
	{
		mlx_delete_image(game->mlx, game->img);
		mlx_terminate(game->mlx);
		ft_putstr_fd("Error\nFailed to put image to window\n", 2);
		return (1);
	}
	if (load_textures(game))
		return (1);
	return (0);
}
