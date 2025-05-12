#include "cub3d.h"

void rotate_player(t_game *game, double angle)
{
    double old_dir_x;
    double old_plane_x;

    // Save current direction and plane x components
    old_dir_x = game->player.dir_x;
    old_plane_x = game->player.plane_x;
    game->player.dir_x = game->player.dir_x * cos(angle) - game->player.dir_y * sin(angle);
    game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y * cos(angle);
    game->player.plane_x = game->player.plane_x * cos(angle) - game->player.plane_y * sin(angle);
    game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y * cos(angle);
}


void	update_player(t_game *game, double move_x, double move_y)
{
    // init_mlx(game);
    // mlx_key_hook(game->mlx, control_player, game);
    // mlx_loop_hook(game->mlx, render_graphics, game);
    // mlx_loop(game->mlx);
    // mlx_terminate(game->mlx);
    clean_exit(game);
}