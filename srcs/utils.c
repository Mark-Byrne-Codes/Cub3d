#include "../../include/cub3d.h"

void clean_exit(t_game *game, char *msg)
{
    (void)game;
    if (msg)
        ft_putstr_fd(msg, 2);
    // if (game)
    // {
    //     free_map(game);
    //     if (game->mlx)
    //         mlx_terminate(game->mlx);
    //     free(game);
    // }
    exit(0);
}