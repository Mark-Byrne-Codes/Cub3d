/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:49:27 by mbyrne            #+#    #+#             */
/*   Updated: 2025/05/25 14:27:04 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Initializes MLX42 window and image
 * 
 * @param game Pointer to game structure
 * @return int 0 on success, 1 on failure
 */
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

/**
 * @brief Initializes game components including MLX, player, and textures
 * 
 * @param game Pointer to game structure
 * @return int 0 on success, 1 on failure
 */
int	init_game(t_game *game)
{
	if (init_mlx(game))
		return (1);
	game->player.pos.x = game->map.player_x + 0.5;
	game->player.pos.y = game->map.player_y + 0.5;
	game->player.dir.x = 0;
	game->player.dir.y = 0;
	game->player.plane.x = 0;
	game->player.plane.y = 0;
	game->graphics.north = load_image(game, game->map.north_texture);
	game->graphics.south = load_image(game, game->map.south_texture);
	game->graphics.east = load_image(game, game->map.east_texture);
	game->graphics.west = load_image(game, game->map.west_texture);
	set_player_dir(game, game->map.start_dir);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
	{
		mlx_delete_image(game->mlx, game->img);
		mlx_terminate(game->mlx);
		ft_putstr_fd("Error\nFailed to put image to window\n", 2);
		return (1);
	}
	return (0);
}

/**
 * @brief Selects appropriate texture based on ray direction and side hit
 * 
 * @param game Pointer to game structure
 * @param ray Pointer to ray structure
 * @return mlx_image_t* Selected texture image
 */
mlx_image_t	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			return (game->graphics.east);
		else
			return (game->graphics.west);
	}
	else
	{
		if (ray->dir.y > 0)
			return (game->graphics.south);
		else
			return (game->graphics.north);
	}
}

/**
 * @brief Loads texture from file and converts it to MLX image
 * 
 * @param game Pointer to game structure
 * @param path Path to texture file
 * @return mlx_image_t* Created image from texture
 */
mlx_image_t	*load_image(t_game *game, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		clean_exit(game, "Failed to load texture\n");
	image = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		clean_exit(game, "Failed to convert texture to image\n");
	return (image);
}

/**
 * @brief Main rendering function, clears screen and performs raycasting
 * 
 * @param param Pointer to game structure (passed as void*)
 */
void	render_graphics(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_memset(game->img->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	raycast(game);
}
