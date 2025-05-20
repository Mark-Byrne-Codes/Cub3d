#include "../../include/cub3d.h"

mlx_image_t	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (game->graphics.east);
		else
			return (game->graphics.west);
	}
	else
	{
		if (ray->dir_y > 0)
			return (game->graphics.south);
		else
			return (game->graphics.north);
	}
}

mlx_image_t	*load_image(t_game *game, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		clean_exit(game, "Failed to load texture");
	image = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		clean_exit(game, "Failed to convert texture to image");
	return (image);
}

void	render_graphics(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	memset(game->img->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	raycast(game);
}
