/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:49:23 by mbyrne            #+#    #+#             */
/*   Updated: 2025/05/22 08:49:24 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_ray(t_ray *ray, t_game *game, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)game->img->width - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	ray->hit = 0;
}

static void	calc_step(t_ray *r, t_game *g)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (g->player.pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - g->player.pos_x) * r->delta_dist_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (g->player.pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - g->player.pos_y) * r->delta_dist_y;
	}
}

static void	perform_dda(t_ray *ray, t_game *game)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x >= 0 && ray->map_x < game->map.max_width
			&& ray->map_y >= 0 && ray->map_y < game->map.height
			&& game->map.map_data[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calc_projection(t_ray *r, t_game *g)
{
	double	p[2];
	int		screen_h;

	p[0] = g->player.pos_x;
	p[1] = g->player.pos_y;
	screen_h = g->img->height;
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - p[0] + (1 - r->step_x) / 2) / r->dir_x;
	else
		r->perp_wall_dist = (r->map_y - p[1] + (1 - r->step_y) / 2) / r->dir_y;
	if (r->perp_wall_dist <= 0.001)
		r->perp_wall_dist = 0.001;
	r->line_height = (int)(screen_h / r->perp_wall_dist);
	if (r->line_height > HEIGHT * 10)
		r->line_height = HEIGHT * 10;
	r->draw_start = -r->line_height / 2 + screen_h / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + screen_h / 2;
	if (r->draw_end >= screen_h)
		r->draw_end = screen_h - 1;
}

void	raycast(t_game *game)
{
	int			x;
	mlx_image_t	*tex;

	x = 0;
	while (x < (int)game->img->width)
	{
		init_ray(&game->ray, game, x);
		calc_step(&game->ray, game);
		perform_dda(&game->ray, game);
		calc_projection(&game->ray, game);
		tex = select_texture(game, &game->ray);
		game->ray.tex_x = calculate_tex_x(&game->ray, tex, &game->player);
		draw_vertical_line(game, x, &game->ray, tex);
		x++;
	}
}
