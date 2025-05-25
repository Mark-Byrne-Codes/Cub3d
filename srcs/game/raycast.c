/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:49:23 by mbyrne            #+#    #+#             */
/*   Updated: 2025/05/25 16:27:12 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Initializes ray properties for casting
 * 
 * @param ray Pointer to ray structure
 * @param game Pointer to game structure
 * @param x Current screen column being processed
 */
static void	init_ray(t_ray *ray, t_game *game, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)game->img->width - 1;
	ray->dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	ray->dir.y = game->player.dir.y + game->player.plane.y * camera_x;
	ray->map.x = (int)game->player.pos.x;
	ray->map.y = (int)game->player.pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	if (ray->dir.x == 0)
		ray->delta_dist.x = HUGE_DIST;
	if (ray->dir.y == 0)
		ray->delta_dist.y = HUGE_DIST;
	ray->hit = 0;
}

/**
 * @brief Calculates ray step direction and initial side distances
 * 
 * @param r Pointer to ray structure
 * @param g Pointer to game structure
 */
static void	calc_ray_step(t_ray *r, t_game *g)
{
	if (r->dir.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (g->player.pos.x - r->map.x) * r->delta_dist.x;
	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = (r->map.x + 1.0 - g->player.pos.x) * r->delta_dist.x;
	}
	if (r->dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = (g->player.pos.y - r->map.y) * r->delta_dist.y;
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = (r->map.y + 1.0 - g->player.pos.y) * r->delta_dist.y;
	}
}

/**
 * @brief Performs Digital Differential Analysis (DDA) algorithm
 * 
 * @param ray Pointer to ray structure
 * @param game Pointer to game structure
 */
static void	perform_dda_algo(t_ray *ray, t_game *game)
{
	while (!ray->hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (ray->map.x >= 0 && ray->map.x < game->map.max_width
			&& ray->map.y >= 0 && ray->map.y < game->map.height
			&& game->map.map_data[(int)ray->map.y][(int)ray->map.x] == '1')
			ray->hit = 1;
	}
}

/**
 * @brief Calculates wall projection and drawing range
 * 
 * @param r Pointer to ray structure
 * @param g Pointer to game structure
 */
static void	calc_wall_projection(t_ray *r, t_game *g)
{
	double	pos_x;
	double	pos_y;
	int		screen_h;

	pos_x = g->player.pos.x;
	pos_y = g->player.pos.y;
	screen_h = g->img->height;
	if (r->side == 0)
		r->perp_wall_dist = (r->map.x - pos_x + (1 - r->step.x) / 2) / r->dir.x;
	else
		r->perp_wall_dist = (r->map.y - pos_y + (1 - r->step.y) / 2) / r->dir.y;
	if (r->perp_wall_dist <= MIN_DIST)
		r->perp_wall_dist = MIN_DIST;
	calc_draw_range(r, screen_h);
}

/**
 * @brief Main raycasting function - casts rays for each screen column
 * 
 * @param game Pointer to game structure
 */
void	raycast(t_game *game)
{
	int			x;
	mlx_image_t	*tex;

	x = 0;
	while (x < (int)game->img->width)
	{
		init_ray(&game->ray, game, x);
		calc_ray_step(&game->ray, game);
		perform_dda_algo(&game->ray, game);
		calc_wall_projection(&game->ray, game);
		tex = select_texture(game, &game->ray);
		game->ray.tex_x = calculate_tex_x(&game->ray, tex, &game->player);
		draw_vertical_line(game, x, &game->ray, tex);
		x++;
	}
}
