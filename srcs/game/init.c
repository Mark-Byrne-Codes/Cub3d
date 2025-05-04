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
    return (0);
}   


int init_game(t_game *game)
{
    int     x;
    int     y;

    x = init_mlx(game);
    if (x)
    {
        return (1);
    }
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            mlx_put_pixel(game->img, x, y, 0x000000FF);
            x++;
        }
        y++;
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
