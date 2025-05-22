/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:49:17 by mbyrne            #+#    #+#             */
/*   Updated: 2025/05/22 08:49:18 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!game->mlx)
	{
		ft_putstr_fd("Error\nFailed to initialize MLX\n", 2);
		return (1);
	}
	game->win = game->mlx->window;
	if (!game->win)
	{
		ft_putstr_fd("Error\nFailed to get window\n", 2);
		mlx_terminate(game->mlx);
		return (1);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		mlx_terminate(game->mlx);
		ft_putstr_fd("Error\nFailed to create image\n", 2);
		return (1);
	}
	return (0);
}

static void	init_graphics(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0;
	game->graphics.north = load_image(game, game->map.north_texture);
	game->graphics.south = load_image(game, game->map.south_texture);
	game->graphics.east = load_image(game, game->map.east_texture);
	game->graphics.west = load_image(game, game->map.west_texture);
}

int	init_game(t_game *game)
{
	init_graphics(game);
	set_player_dir(game, game->map.start_dir);
	if (init_mlx(game))
		return (1);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
	{
		mlx_delete_image(game->mlx, game->img);
		mlx_terminate(game->mlx);
		ft_putstr_fd("Error\nFailed to put image to window\n", 2);
		return (1);
	}
	return (0);
}
