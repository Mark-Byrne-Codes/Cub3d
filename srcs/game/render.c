#include "../../include/cub3d.h"

static void	render_map(t_game *game)
{
    int		x;
    int		y;
    int		map_x;
    int		map_y;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            map_x = (int)((float)x / WIDTH * 8);
            map_y = (int)((float)y / HEIGHT * 8);
            if (map_x < MAP_WIDTH && map_y < MAP_HEIGHT
                && game->map.map[map_y][map_x] == '1')
                mlx_put_pixel(game->img, x, y, 0xFFFFFFFF);
            else
                mlx_put_pixel(game->img, x, y, 0x000000FF);
            x++;
        }
        y++;
    }
}

static void	render_player(t_game *game)
{
	int	player_px;
	int	player_py;

	player_px = (int)(game->player.x * (WIDTH / 8.0));
	player_py = (int)(game->player.y * (HEIGHT / 8.0));
	if (player_px >= 0 && player_px < WIDTH
		&& player_py >= 0 && player_py < HEIGHT)
		mlx_put_pixel(game->img, player_px, player_py, 0xFF0000FF);
}

static void	draw_view_line(t_game *game)
{
	int		i;
	double	dir_x;
	double	dir_y;
	int		pixel_x;
	int		pixel_y;

	pixel_x = (int)(game->player.x * (WIDTH / 8.0));
	pixel_y = (int)(game->player.y * (HEIGHT / 8.0));
	dir_x = game->player.dir_x;
	dir_y = game->player.dir_y;
	i = 0;
	while (i < 200)
	{
		int x = pixel_x + (int)(dir_x * i);
		int y = pixel_y + (int)(dir_y * i);
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			mlx_put_pixel(game->img, x, y, 0x00FF00FF);
		i++;
	}
}

void	render_graphics(void *param)
{
    t_game	*game;

    game = (t_game *)param;
    

    render_map(game);
    render_player(game);
    draw_view_line(game);
    
    mlx_image_to_window(game->mlx, game->img, 0, 0);
}
