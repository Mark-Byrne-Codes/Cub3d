#include "../../../include/cub3d.h"


int init_game(t_game *game)
{
    game->mlx = mlx_init(width, height, "cub3D", false);
    if (!game->mlx)
    {
        ft_putstr_fd("Error\nFailed to initialize MLX.\n", 2);
        return (1);
    }
    game->win = game->mlx->window;
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->img)
    {
        mlx_terminate(game->mlx);
        ft_putstr_fd("Error\nFailed to create image.\n", 2);
        return (1);
    }
    if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
    {
        mlx_delete_image(game->mlx, game->img);
        mlx_terminate(game->mlx);
        ft_putstr_fd("Error\nFailed to put image to window.\n", 2);
        return (1);
    }
    return (0);
}



void render_graphics(t_game *game)
{

}




