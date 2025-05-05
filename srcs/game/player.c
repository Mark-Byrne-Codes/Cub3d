#include "../../include/cub3d.h"


void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;

	// Save the current direction x before updating it
	old_dir_x = game->player.dir_x;

	// Rotate the direction vector using 2D rotation matrix:
	// [x'] = [cosθ -sinθ] * [x]
	// [y']   [sinθ  cosθ]  * [y]
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);

}


void	update_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = game->player.x + move_x;
	new_y = game->player.y + move_y;
	if (new_x < 0 || new_x >= MAP_WIDTH || new_y < 0 || new_y >= MAP_HEIGHT)
		return ;
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (game->map.map[map_y][map_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void control_player(mlx_key_data_t keydata, void *param)
{
    t_game *game;
    double move;
    double rotate;

    move = 0.1;
    rotate = 0.05;
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
        if (keydata.key == MLX_KEY_RIGHT)
            rotate_player(game, rotate);
        if (keydata.key == MLX_KEY_LEFT)
            rotate_player(game, -rotate);
        if (keydata.key == MLX_KEY_ESCAPE)
            mlx_close_window(game->mlx);
    }
}