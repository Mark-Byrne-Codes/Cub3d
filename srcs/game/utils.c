#include "../../../include/cub3d.h"

void clean_exit(t_game *game)
{
    if (game->graphics)
    {
        if (game->graphics->north)
            mlx_delete_image(game->mlx, game->graphics->north);
        if (game->graphics->south)
            mlx_delete_image(game->mlx, game->graphics->south);
        if (game->graphics->west)
            mlx_delete_image(game->mlx, game->graphics->west);
        if (game->graphics->east)
            mlx_delete_image(game->mlx, game->graphics->east);
        free(game->graphics);
    }
    // if(game->map)
    //     free_map(game->map->map);
    if(game->mlx)
        mlx_terminate(game->mlx);
    if (game)
        free(game);
}

void	handle_esc(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		clean_exit(game);
		exit(0);
	}
}