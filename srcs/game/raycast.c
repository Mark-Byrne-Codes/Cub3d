#include "../../include/cub3d.h"

/**
 * Initializes ray properties for a screen column
 * @param ray Ray structure to initialize
 * @param game Main game structure containing player/map data
 * @param x Current screen column being processed
 * @note Calculates ray direction, map starting position, 
 *       and delta distances for DDA algorithm
 */
static void	init_ray(t_ray *ray, t_game *game, int x)
{
	const double	camera_x = 2 * x / (double)game->img->width - 1;

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

/**
 * Determines ray stepping direction and initial side distances
 * @param ray Contains ray direction and delta distances
 * @param game Used for player position reference
 * @note Sets step direction (-1 or 1) and calculates
 *       initial distance to first grid boundary
 */
static void	calc_step(t_ray *ray, t_game *game)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y)
			* ray->delta_dist_y;
	}
}

/**
 * Executes Digital Differential Analysis algorithm
 * @param ray Current ray being cast
 * @param game Contains map data for collision detection
 * @note Steps through grid until hitting wall or map boundary,
 *       tracking which side of the wall was hit
 */
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
		if ((ray->map_x >= 0 && ray->map_x < game->map.width
				&& ray->map_y >= 0 && ray->map_y < game->map.height)
			&& (game->map.map[ray->map_y][ray->map_x] == '1'))
			ray->hit = 1;
		else if (ray->map_x < 0 || ray->map_x >= game->map.width
			|| ray->map_y < 0 || ray->map_y >= game->map.height)
			ray->hit = 1;
	}
}

/**
 * Calculates wall projection parameters
 * @param ray Contains hit information and distances
 * @param game Provides screen dimensions and player position
 * @note Determines wall height, draw start/end positions,
 *       and vertical line boundaries for rendering
 */
static void	calc_projection(t_ray *ray, t_game *game)
{
	const double	pos_x = game->player.pos_x;
	const double	pos_y = game->player.pos_y;
	const int		screen_h = game->img->height;

	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - pos_x
				+ (1 - ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - pos_y
				+ (1 - ray->step_y) / 2.0) / ray->dir_y;
	ray->line_height = (int)(screen_h / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + screen_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + screen_h / 2;
	if (ray->draw_end >= screen_h)
		ray->draw_end = screen_h - 1;
}

/**
 * Main raycasting loop for 3D projection
 * @param game Contains all game state and rendering context
 * @note For each screen column: casts ray, calculates wall hit,
 *       determines texture position, and draws vertical stripe
 */
void	raycast(t_game *game)
{
	int			x;
	mlx_image_t	*tex;
	int			tex_x;

	x = -1;
	while (++x < (int)game->img->width)
	{
		init_ray(&game->ray, game, x);
		calc_step(&game->ray, game);
		perform_dda(&game->ray, game);
		calc_projection(&game->ray, game);
		tex = select_texture(game, &game->ray);
		tex_x = calculate_tex_x(&game->ray, tex, &game->player);
		draw_vertical_line(game, x, &game->ray, tex);
	}
}