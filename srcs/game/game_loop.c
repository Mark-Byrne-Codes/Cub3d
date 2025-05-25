/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:49:29 by mbyrne            #+#    #+#             */
/*   Updated: 2025/05/25 14:00:25 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Rotates the player's direction and plane vectors by a given angle
 * 
 * @param g Pointer to the game structure
 * @param a Angle in radians to rotate the player
 */
void	rotate_player(t_game *g, double a)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_a;
	double	sin_a;

	old_dir_x = g->player.dir.x;
	old_plane_x = g->player.plane.x;
	cos_a = cos(a);
	sin_a = sin(a);
	g->player.dir = vec_rotate(g->player.dir, a);
	g->player.plane = vec_rotate(g->player.plane, a);
}

/**
 * @brief Updates the player's position based on movement vectors
 * 
 * @param g Pointer to the game structure
 * @param mv_x Movement vector in x direction
 * @param mv_y Movement vector in y direction
 */
void	update_player(t_game *g, double mv_x, double mv_y)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = g->player.pos.x + mv_x;
	new_y = g->player.pos.y + mv_y;
	if (new_x < 0 || new_x >= g->map.max_width || new_y < 0
		|| new_y >= g->map.height)
		return ;
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (g->map.map_data[map_y][map_x] != '1')
	{
		g->player.pos.x = new_x;
		g->player.pos.y = new_y;
	}
}

/**
 * @brief Handles player movement based on key input
 * 
 * @param g Pointer to the game structure
 * @param keydata MLX key data structure
 * @param move Movement speed
 */
static void	handle_movement(t_game *g, mlx_key_data_t keydata, double move)
{
	if (keydata.key == MLX_KEY_W)
		update_player(g, g->player.dir.x * move, g->player.dir.y * move);
	else if (keydata.key == MLX_KEY_S)
		update_player(g, -g->player.dir.x * move, -g->player.dir.y * move);
	else if (keydata.key == MLX_KEY_A)
		update_player(g, -g->player.dir.y * move, g->player.dir.x * move);
	else if (keydata.key == MLX_KEY_D)
		update_player(g, g->player.dir.y * move, -g->player.dir.x * move);
}

/**
 * @brief Main player control function, handles key inputs
 * 
 * @param keydata MLX key data structure
 * @param param Pointer to game structure (passed as void*)
 */
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

/**
 * @brief Main game loop function
 * 
 * @param game Pointer to the game structure
 * @return int Returns 0 on success, 1 on initialization failure
 */
int	run_game(t_game *game)
{
	if (init_game(game))
		return (1);
	mlx_key_hook(game->mlx, control_player, game);
	mlx_loop_hook(game->mlx, render_graphics, game);
	mlx_loop(game->mlx);
	return (0);
}
