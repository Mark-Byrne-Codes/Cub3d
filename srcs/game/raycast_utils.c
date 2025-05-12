#include "../../include/cub3d.h"



int calculate_tex_x(t_ray *ray, mlx_image_t *tex, t_player *player)
{
    double  wall_x;

    if (ray->side == 0)
        wall_x = player->pos_y + ray->perp_wall_dist * ray->dir_y;
    else
        wall_x = player->pos_x + ray->perp_wall_dist * ray->dir_x;
    wall_x -= floor(wall_x);
    ray->tex_x = (int)(wall_x * (double)tex->width);
    if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1 && ray->dir_y < 0))
        ray->tex_x = tex->width - ray->tex_x - 1;
    
    return (ray->tex_x);
}

// Calculates the step size for moving through the texture vertically
// and the initial vertical position on the texture.
// Parameters:
//   ray: A pointer to the t_ray structure containing information about the wall projection (line height, draw start).
//   tex: A pointer to the mlx_image_t structure representing the current texture.
//   step: A pointer to a double where the vertical step size on the texture will be stored.
//   tex_pos: A pointer to a double where the initial vertical position on the texture will be stored.
//   win_height: The height of the game window.
static void calculate_step_and_pos(t_ray *ray, mlx_image_t *tex, int win_height)
{
    ray->step = (double)tex->height / ray->line_height;
    ray->tex_pos = (ray->draw_start - win_height / 2 + ray->line_height / 2) * (ray->step);
}

// Gets the color of a specific pixel from the texture.
// Parameters:
//   tex: A pointer to the mlx_image_t structure representing the texture.
//   tex_x: The x-coordinate of the pixel on the texture.
//   tex_y: The y-coordinate of the pixel on the texture.
static uint32_t get_texture_color(mlx_image_t *tex, int tex_x, int tex_y)
{
    int     tex_index;

    tex_y = (tex_y % tex->height);
    tex_index = (tex_y * tex->width + tex_x) * 4;
    return (
        (tex->pixels[tex_index + 0] << 24)
        | (tex->pixels[tex_index + 1] << 16)
        | (tex->pixels[tex_index + 2] << 8)
        | (tex->pixels[tex_index + 3])
    );
}



// Draws a vertical line on the screen representing a slice of the wall texture.
// Parameters:
//   game: A pointer to the t_game structure containing game data (image).
//   x: The x-coordinate on the screen where the vertical line will be drawn.
//   ray: A pointer to the t_ray structure containing information about the wall projection (draw start/end).
//   tex: A pointer to the mlx_image_t structure representing the wall texture.
//   tex_x: The x-coordinate on the texture to sample for this vertical line.
void draw_vertical_line(t_game *game, int x, t_ray *ray, mlx_image_t *tex)
{
    int y;
    
    calculate_step_and_pos(ray, tex, game->img->height);
    y = 0;
    while (y < ray->draw_start)
    {
        mlx_put_pixel(game->img, x, y, create_rgba(game->graphics.ceiling_color));
        y++;
    }
    y = ray->draw_start;
    while (y <= ray->draw_end)
    {
        int tex_y = (int)ray->tex_pos & (tex->height - 1);
        ray->color = get_texture_color(tex, ray->tex_x, tex_y);
        mlx_put_pixel(game->img, x, y, ray->color);
        ray->tex_pos += ray->step;
        y++;
    }
    while (y < (int)game->img->height)
    {
        mlx_put_pixel(game->img, x, y, create_rgba(game->graphics.floor_color));
        y++;
    }
}


