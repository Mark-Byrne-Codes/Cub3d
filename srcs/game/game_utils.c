/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:49:15 by mbyrne            #+#    #+#             */
/*   Updated: 2025/05/25 14:32:46 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Rotates a 2D vector by a given angle
 * 
 * @param v Original vector to rotate
 * @param angle Angle in radians to rotate by
 * @return t_vec Rotated vector
 */
t_vec	vec_rotate(t_vec v, double angle)
{
	t_vec	rotated_v;

	rotated_v.x = v.x * cos(angle) - v.y * sin(angle);
	rotated_v.y = v.x * sin(angle) + v.y * cos(angle);
	return (rotated_v);
}

/**
 * @brief Clamps a value between minimum and maximum bounds
 * 
 * @param value Pointer to the value to clamp
 * @param min_val Minimum allowed value
 * @param max_val Maximum allowed value
 */
void	clamp_value(int *value, int min_val, int max_val)
{
	if (*value < min_val)
		*value = min_val;
	if (*value > max_val)
		*value = max_val;
}

/**
 * @brief Creates an RGBA color value from color components
 * 
 * @param color Struct containing r, g, b components
 * @return uint32_t Packed 32-bit RGBA value
 */
uint32_t	create_rgba(t_color color)
{
	return (((uint32_t)color.r << 24) | ((uint32_t)color.g << 16)
		| ((uint32_t)color.b << 8) | 0xFF);
}

/**
 * @brief Sets player direction and camera plane based on starting direction
 * 
 * @param game Pointer to game structure
 * @param dir Starting direction character (N/S/E/W)
 */
void	set_player_dir(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
		game->player.plane.x = -0.66;
	}
	else if (dir == 'S')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
		game->player.plane.x = 0.66;
	}
	else if (dir == 'E')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
		game->player.plane.y = -0.66;
	}
	else if (dir == 'W')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
		game->player.plane.y = 0.66;
	}
}

/**
 * @brief Cleans up game resources and exits program
 * 
 * @param game Pointer to game structure
 * @param msg Optional error message to display before exiting
 */
void	clean_exit(t_game *game, char *msg)
{
	if (!game)
		exit(0);
	free_map(game);
	if (msg)
		ft_putstr_fd(msg, 2);
	if (game->mlx)
	{
		if (game->img)
			mlx_delete_image(game->mlx, game->img);
		if (game->graphics.north)
			mlx_delete_image(game->mlx, game->graphics.north);
		if (game->graphics.south)
			mlx_delete_image(game->mlx, game->graphics.south);
		if (game->graphics.west)
			mlx_delete_image(game->mlx, game->graphics.west);
		if (game->graphics.east)
			mlx_delete_image(game->mlx, game->graphics.east);
		mlx_terminate(game->mlx);
	}
	free(game);
	exit(0);
}
