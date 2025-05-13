#include "../../include/cub3d.h"

void rotate_player(t_game *game, double angle)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = game->player.dir_x;
    old_plane_x = game->player.plane_x;
    game->player.dir_x = game->player.dir_x * cos(angle) - game->player.dir_y * sin(angle);
    game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y * cos(angle);
    game->player.plane_x = game->player.plane_x * cos(angle) - game->player.plane_y * sin(angle);
    game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y * cos(angle);
}

void	update_player(t_game *game, double move_x, double move_y)
{

	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = game->player.pos_x + move_x;
	new_y = game->player.pos_y + move_y;
	if (new_x < 0 || new_x >= game->map.width || new_y < 0 || new_y >= game->map.height)
		return ;
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (game->map.map_data[map_y][map_x] != '1')
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

void control_player(mlx_key_data_t keydata, void *param)
{
    t_game *game;
    double move;
    double rotate;

    move = MOVE_SPEED;
    rotate = ROTATE_SPEED;
    game = (t_game *)param;
    handle_esc(keydata, game);
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_W)
            update_player(game, game->player.dir_x * move, game->player.dir_y * move);
        if (keydata.key == MLX_KEY_S)
            update_player(game, -game->player.dir_x * move, -game->player.dir_y * move);
        if (keydata.key == MLX_KEY_A)
            update_player(game, -game->player.dir_y * move, game->player.dir_x * move);
        if (keydata.key == MLX_KEY_D)
            update_player(game, game->player.dir_y * move, -game->player.dir_x * move);
        if (keydata.key == MLX_KEY_LEFT)
            rotate_player(game, rotate);
        if (keydata.key == MLX_KEY_RIGHT)
            rotate_player(game, -rotate);
    }
}

int run_game(t_game *game)
{
	if (init_game(game))
		return (1);
    game->player.pos_x = game->map.player_x + 0.5;
    game->player.pos_y = game->map.player_y + 0.5;
	mlx_key_hook(game->mlx, control_player, game);
	mlx_loop_hook(game->mlx, render_graphics, game);
	mlx_loop(game->mlx);
	return (0);
}