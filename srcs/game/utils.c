#include "../../include/cub3d.h"

void clean_exit(t_game *game, char *msg)
{
    (void)game;
    if (msg)
        ft_putstr_fd(msg, 2);
    // if(game->map)
    //     free_map(game->map->map);
    // if(game->mlx)
    //     mlx_terminate(game->mlx);
    // if (game)
    //     free(game);
}

void	handle_esc(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		clean_exit(game, NULL);
		exit(0);
	}
}