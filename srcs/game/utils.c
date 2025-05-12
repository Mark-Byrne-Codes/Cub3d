#include "../../include/cub3d.h"

void clean_exit(t_game *game, char *msg)
{

    if (msg)
        ft_putstr_fd(msg, 2);
    // if(game->map)
    //     free_map(game->map->map);
    // if(game->mlx)
    //     mlx_terminate(game->mlx);
    if (game)
        free(game);
}

uint32_t create_rgba(t_color color)
{
    uint8_t r;
    uint8_t g;
    uint8_t b;

    r = (uint8_t)color.r;
    g = (uint8_t)color.g;
    b = (uint8_t)color.b;
    
    return ((uint32_t)r << 24) | 
           ((uint32_t)g << 16) | 
           ((uint32_t)b << 8) | 
           0xFF;
}

void	handle_esc(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		clean_exit(game, NULL);
		exit(0);
	}
}