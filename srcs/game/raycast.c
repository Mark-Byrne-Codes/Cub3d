#include "../../include/cub3d.h"

/**
 * Initializes ray properties for a screen column
 * @param ray Ray structure to initialize
 * @param game Main game structure containing player/map data
 * @param x Current screen column being processed
 * @note The function performs the following steps:
 * 1. Converts screen x-coordinate to camera space (-1 to +1)
 * 2. Calculates ray direction using player direction and camera plane
 * 3. Sets initial grid cell position
 * 4. Calculates delta distances (distance needed to move from one grid cell to the next)
 * 5. Handles division by zero cases for horizontal/vertical rays
 * 6. Initializes the hit flag
 */
static void	init_ray(t_ray *ray, t_game *game, int x)
{
	double camera_x;

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

/**
 * @brief Calculate step direction and initial side distances for DDA algorithm
 *
 * This function determines which direction the ray will step through the grid
 * (positive or negative in both x and y) and calculates the initial side distances.
 * Side distances represent how far the ray must travel from its starting point
 * to reach the next x or y grid line.
 *
 * @param ray Pointer to the ray structure to be updated
 * @param game Pointer to the game structure containing player position
 * 
 * @details The function performs the following steps:
 * 1. Determines the x-direction step (-1 for left, 1 for right) based on ray direction
 * 2. Calculates initial x-side distance to the nearest grid boundary
 * 3. Determines the y-direction step (-1 for up, 1 for down) based on ray direction
 * 4. Calculates initial y-side distance to the nearest grid boundary
 *
 * @note Side distances are scaled by delta distances to normalize step lengths.
 * This makes the DDA algorithm independent of ray length and direction.
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
 * @brief Perform the DDA (Digital Differential Analysis) algorithm for raycasting
 *
 * This function advances the ray through the map grid using the DDA algorithm until
 * it hits a wall or goes out of bounds. DDA is an efficient algorithm for traversing
 * a grid along a ray path, always stepping to the next grid cell in the direction
 * that requires the shortest distance to travel.
 *
 * @param ray Pointer to the ray structure containing direction and step information
 * @param game Pointer to the game structure containing the map data
 * 
 * @details The function performs the following steps:
 * 1. Loops until a wall is hit or the ray goes out of bounds
 * 2. Determines whether to step in the x or y direction (whichever side distance is smaller)
 * 3. Updates the ray's position in the grid and its side distances
 * 4. Records which side of the wall was hit (for texture mapping and lighting)
 * 5. Checks if the new position contains a wall or is out of bounds
 *
 * @note The 'side' variable is set to 0 for x-side hits (vertical walls) and 1 for
 * y-side hits (horizontal walls). This will be used later for shading and texture mapping.
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
 * @brief Calculate wall projection parameters for rendering
 * 
 * This function calculates the perpendicular wall distance, line height,
 * and vertical drawing range for the current raycast column. These values
 * determine how the wall slice will be projected onto the screen while
 * maintaining perspective correction.
 *
 * @param ray Pointer to the ray structure containing intersection data
 * @param game Pointer to the game structure with player and display info
 * 
 * @details The function performs these key operations:
 * 1. Calculates perpendicular distance to wall to avoid fish-eye distortion
 * 2. Determines vertical line height based on distance and screen height
 * 3. Calculates starting and ending Y coordinates for wall rendering
 * 4. Clamps values to screen boundaries to prevent overflow
 * 
 * @note The perpendicular distance calculation differs for x/y side hits
 * to ensure proper perspective correction. The minimum distance clamp
 * prevents division by zero in rendering calculations.
 */
static void	calc_projection(t_ray *ray, t_game *game)
{
	double	pos_x;
	double	pos_y;
	int		screen_h;


	pos_x = game->player.pos_x;
	pos_y = game->player.pos_y;
	screen_h = game->img->height;
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - pos_x
				+ (1 - ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - pos_y
				+ (1 - ray->step_y) / 2.0) / ray->dir_y;
	if (ray->perp_wall_dist <= 0.001)
		ray->perp_wall_dist = 0.001;
	ray->line_height = (int)(screen_h / ray->perp_wall_dist);
	if (ray->line_height > HEIGHT * 10)
		ray->line_height = HEIGHT * 10;
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
