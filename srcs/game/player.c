// #include "../../../include/cub3d.h"

// void rotate_player(t_game *game, double angle)
// {
//     double old_dir_x;
//     double old_plane_x;

// }

// void	update_player(t_game *game, double new_x, double new_y)
// {
// 	if (new_y < 0 || new_y >= game->map->height || new_x < 0 || \
// 		new_x >= game->map->width)
// 	{
// 		return ;
// 	}
// 	mlx_image_to_window(game->mlx, game->graphics, \
// 		game->player->pos.x, game->player->pos.y);
// 	game->player->pos.x = new_x;
// 	game->player->pos.y = new_y;
// 	mlx_image_to_window(game->mlx, game->graphics, new_x, new_y);
// }

// void	control_player(mlx_key_data_t keydata, void *param)
// {
// 	t_game	*game;
// 	double			move;
// 	double			rotate;

//     move = 0.1;
//     rotate = 0.05;
// 	game = (t_game *)param;
// 	handle_esc(keydata, game);
//     if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
//     {
//         if (keydata.key == MLX_KEY_W)
//             update_player(game, game->player->dir.x * move, game->player->dir.y * move);
//         if (keydata.key == MLX_KEY_S)
//             update_player(game, -game->player->dir.x * move, -game->player->dir.y * move);
//         if (keydata.key == MLX_KEY_A)
//             update_player(game, -game->player->dir.y * move, game->player->dir.x * move);
//         if (keydata.key == MLX_KEY_D)
//             update_player(game, game->player->dir.y * move, -game->player->dir.x * move);
//         if (keydata.key == MLX_KEY_LEFT)
//             rotate_player(game, rotate);
//         if (keydata.key == MLX_KEY_RIGHT)
//             rotate_player(game, -rotate);
//     }
// }