#include "../../include/cub3d.h"


// Selects the appropriate texture based on which side of the wall was hit
// and the direction of the ray.
// Parameters:
//   game: A pointer to the t_game structure containing game data, including loaded textures.
//   ray: A pointer to the t_ray structure containing information about the ray hit (side, direction).
mlx_image_t  *select_texture(t_game *game, t_ray *ray)
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


static mlx_image_t	*load_image(t_game *game, const char *path)
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

/*
 * Loads all graphical assets (images) required for the game.
 * @param game Pointer to the game state structure.
 */
int	load_textures(t_game *game)
{

	game->graphics.north = load_image(game, game->map.north_texture);
    game->graphics.south = load_image(game, game->map.south_texture);
    game->graphics.east = load_image(game, game->map.east_texture);
    game->graphics.west = load_image(game, game->map.west_texture);
    return (0);
}


void	render_graphics(void *param)
{
    t_game	*game;
    
    game =(t_game *)param;
    memset(game->img->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
    raycast(game);
    //render_minimap(game);
}

