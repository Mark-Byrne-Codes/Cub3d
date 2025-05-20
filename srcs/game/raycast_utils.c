#include "../../include/cub3d.h"

int	calculate_tex_x(t_ray *ray, mlx_image_t *tex, t_player *p)
{
	double	wall_x;
	bool	mirrored;

	if (ray->side == 0)
		wall_x = p->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = p->pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * tex->width);
	mirrored = (ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y < 0);
	if (mirrored)
		ray->tex_x = tex->width - ray->tex_x - 1;
	return (ray->tex_x);
}

static void	calculate_step_and_pos(t_ray *ray, mlx_image_t *tex, int win_h)
{
	double	vertical_offset;

	ray->step = (double)tex->height / ray->line_height;
	vertical_offset = (ray->draw_start - win_h / 2 + ray->line_height / 2);
	ray->tex_pos = vertical_offset * ray->step;
}

static uint32_t	get_pixel_color(mlx_image_t *tex, int x, int y)
{
	uint8_t	*pixel;

	y %= tex->height;
	pixel = &tex->pixels[(y * tex->width + x) * 4];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

void	draw_vertical_line(t_game *g, int x, t_ray *ray, mlx_image_t *tex)
{
	int	y;

	calculate_step_and_pos(ray, tex, g->img->height);
	y = 0;
	while (y < (int)g->img->height)
	{
		if (y < ray->draw_start)
			mlx_put_pixel(g->img, x, y, create_rgba(g->graphics.ceiling_color));
		else if (y > ray->draw_end)
			mlx_put_pixel(g->img, x, y, create_rgba(g->graphics.floor_color));
		else
		{
			mlx_put_pixel(g->img, x, y, get_pixel_color(tex, ray->tex_x,
					(int)ray->tex_pos & (tex->height - 1)));
			ray->tex_pos += ray->step;
		}
		y++;
	}
}
