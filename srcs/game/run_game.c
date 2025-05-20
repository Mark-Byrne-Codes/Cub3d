#include "../../include/cub3d.h"

void	rotate_player(t_game *g, double a)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_a;
	double	sin_a;

	old_dir_x = g->player.dir_x;
	old_plane_x = g->player.plane_x;
	cos_a = cos(a);
	sin_a = sin(a);
	g->player.dir_x = g->player.dir_x * cos_a - g->player.dir_y * sin_a;
	g->player.dir_y = old_dir_x * sin_a + g->player.dir_y * cos_a;
	g->player.plane_x = g->player.plane_x * cos_a - g->player.plane_y * sin_a;
	g->player.plane_y = old_plane_x * sin_a + g->player.plane_y * cos_a;
}

void	update_player(t_game *g, double mv_x, double mv_y)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = g->player.pos_x + mv_x;
	new_y = g->player.pos_y + mv_y;
	if (new_x < 0 || new_x >= g->map.max_width || new_y < 0
		|| new_y >= g->map.height)
		return ;
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (g->map.map_data[map_y][map_x] != '1')
	{
		g->player.pos_x = new_x;
		g->player.pos_y = new_y;
	}
}

static void	handle_movement(t_game *g, mlx_key_data_t keydata, double move)
{
	if (keydata.key == MLX_KEY_W)
		update_player(g, g->player.dir_x * move, g->player.dir_y * move);
	else if (keydata.key == MLX_KEY_S)
		update_player(g, -g->player.dir_x * move, -g->player.dir_y * move);
	else if (keydata.key == MLX_KEY_A)
		update_player(g, -g->player.dir_y * move, g->player.dir_x * move);
	else if (keydata.key == MLX_KEY_D)
		update_player(g, g->player.dir_y * move, -g->player.dir_x * move);
}

void	control_player(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	double	move;
	double	rotate;

	game = (t_game *)param;
	move = MOVE_SPEED;
	rotate = ROTATE_SPEED;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_exit(game, NULL);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		handle_movement(game, keydata, move);
		if (keydata.key == MLX_KEY_LEFT)
			rotate_player(game, rotate);
		if (keydata.key == MLX_KEY_RIGHT)
			rotate_player(game, -rotate);
	}
}

int	run_game(t_game *game)
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
