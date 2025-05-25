/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:49:20 by mbyrne            #+#    #+#             */
/*   Updated: 2025/05/25 17:09:17 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Calculates the vertical draw range for a wall slice
 * 
 * @param r Pointer to ray structure
 * @param screen_h Screen height in pixels
 */
void	calc_draw_range(t_ray *r, int screen_h)
{
	r->line_height = (int)(screen_h / r->perp_wall_dist);
	clamp_value(&r->line_height, 0, HEIGHT * 10);
	r->draw_start = -r->line_height / 2 + screen_h / 2;
	clamp_value(&r->draw_start, 0, screen_h - 1);
	r->draw_end = r->line_height / 2 + screen_h / 2;
	clamp_value(&r->draw_end, 0, screen_h - 1);
}

/**
 * @brief Calculates the x-coordinate on the texture for the current wall slice
 * 
 * @param ray Pointer to ray structure
 * @param tex Pointer to texture image
 * @param p Pointer to player structure
 * @return int The calculated texture x-coordinate
 */
int	calculate_tex_x(t_ray *ray, mlx_image_t *tex, t_player *p)
{
	double	wall_x;
	bool	mirrored;

	if (ray->side == 0)
		wall_x = p->pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = p->pos.x + ray->perp_wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * tex->width);
	mirrored = (ray->side == 0 && ray->dir.x < 0)
		|| (ray->side == 1 && ray->dir.y < 0);
	if (mirrored)
		ray->tex_x = tex->width - ray->tex_x - 1;
	return (ray->tex_x);
}

/**
 * @brief Calculates texture stepping and initial position for wall rendering
 * 
 * @param ray Pointer to ray structure
 * @param tex Pointer to texture image
 * @param win_h Window height in pixels
 */
static void	calculate_step_and_pos(t_ray *ray, mlx_image_t *tex, int win_h)
{
	double	vertical_offset;

	ray->step_tex = (double)tex->height / ray->line_height;
	vertical_offset = (ray->draw_start - win_h / 2 + ray->line_height / 2);
	ray->tex_pos = vertical_offset * ray->step_tex;
}

/**
 * @brief Gets the color of a pixel from a texture
 * 
 * @param tex Pointer to texture image
 * @param x X-coordinate in texture
 * @param y Y-coordinate in texture
 * @return uint32_t The pixel color in RGBA format
 */
static uint32_t	get_pixel_color(mlx_image_t *tex, int x, int y)
{
	uint8_t	*pixel;

	y = y % tex->height;
	if (y < 0)
		y += tex->height;
	pixel = &tex->pixels[(y * tex->width + x) * BYTES_PER_PIXEL];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

/**
 * @brief Draws a vertical slice of the wall on the screen
 * 
 * @param g Pointer to game structure
 * @param x Screen column to draw
 * @param ray Pointer to ray structure
 * @param tex Pointer to texture image
 */
void	draw_vertical_line(t_game *g, int x, t_ray *ray, mlx_image_t *tex)
{
	uint32_t		color;
	int				y;

	calculate_step_and_pos(ray, tex, g->img->height);
	y = 0;
	while (y < (int)g->img->height)
	{
		if (y < ray->draw_start)
			color = g->graphics.ceiling_rgba;
		else if (y > ray->draw_end)
			color = g->graphics.floor_rgba;
		else
		{
			color = get_pixel_color(tex, ray->tex_x,
					(int)ray->tex_pos & (tex->height - 1));
			ray->tex_pos += ray->step_tex;
		}
		mlx_put_pixel(g->img, x, y, color);
		y++;
	}
}
