#include "../../include/cub3d.h"

int run_game(t_game *game)
{
	if (init_game(game))
		return (1);
	mlx_key_hook(game->mlx, control_player, game);
	mlx_loop_hook(game->mlx, render_graphics, game);
	mlx_loop(game->mlx);
	return (0);
}