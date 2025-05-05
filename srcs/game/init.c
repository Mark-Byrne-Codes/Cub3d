#include "../../include/cub3d.h"

static int init_mlx(t_game *game)
{
    game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
    if (!game->mlx)
    {
        ft_putstr_fd("Error\nFailed to initialize MLX.\n", 2);
        return (1);
    }
    game->win = game->mlx->window;
    if (!game->win)
    {
        printf("Error: Failed to get the window\n");
        mlx_terminate(game->mlx);
        return (1);
    }
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->img)
    {
        mlx_terminate(game->mlx);
        ft_putstr_fd("Error\nFailed to create image.\n", 2);
        return (1);
    }
    return 0;
}   

int init_game(t_game *game)
{
	game->player.x = 3.5;
	game->player.y = 3.5;
	game->player.dir_x = 1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
    if (init_mlx(game))
        return (1);
    if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
    {
        mlx_delete_image(game->mlx, game->img);
        mlx_terminate(game->mlx);
        ft_putstr_fd("Error\nFailed to put image to window.\n", 2);
        return (1);
    }
    return (0);
}


