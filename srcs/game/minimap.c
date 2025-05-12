#include "../../include/cub3d.h"

#define MINIMAP_X 20
#define MINIMAP_Y 20
#define MINIMAP_WIDTH 400
#define MINIMAP_HEIGHT 400
#define MINIMAP_SCALE 20.0
#define MINIMAP_WALL_COLOR 0xFFFFFFFF
#define MINIMAP_FLOOR_COLOR 0x00000077
#define MINIMAP_PLAYER_COLOR 0xFF0000FF
#define MINIMAP_VIEW_COLOR 0x00FF00FF
#define PLAYER_DOT_SIZE 7
#define VIEW_LINE_LENGTH 40
#define VIEW_LINE_STEP 2

static void	draw_minimap_pixel(t_game *game, int x, int y, int color)
{
    if (x >= MINIMAP_X && x < MINIMAP_X + MINIMAP_WIDTH && 
        y >= MINIMAP_Y && y < MINIMAP_Y + MINIMAP_HEIGHT)
        mlx_put_pixel(game->img, x, y, color);
}

static void	render_map(t_game *game)
{
    int	x;
    int	y;
    int	map_x;
    int	map_y;
    double scale_x;
    double scale_y;

    scale_x = (double)MINIMAP_WIDTH / game->map.width;
    scale_y = (double)MINIMAP_HEIGHT / game->map.height;
    y = 0;
    while (y < MINIMAP_HEIGHT)
    {
        x = 0;
        while (x < MINIMAP_WIDTH)
        {
            map_x = floor(x / scale_x);
            map_y = floor(y / scale_y);
            if (map_x >= 0 && map_x < game->map.width &&
                map_y >= 0 && map_y < game->map.height &&
                game->map.map_grid[map_y][map_x] == '1')
                draw_minimap_pixel(game, MINIMAP_X + x, MINIMAP_Y + y, MINIMAP_WALL_COLOR);
            else
                draw_minimap_pixel(game, MINIMAP_X + x, MINIMAP_Y + y, MINIMAP_FLOOR_COLOR);
            x++;
        }
        y++;
    }
}

static void	render_player(t_game *game)
{
    int	px;
    int	py;
    int	i;
    int	j;
    double scale_x;
    double scale_y;

    scale_x = (double)MINIMAP_WIDTH / game->map.width;
    scale_y = (double)MINIMAP_HEIGHT / game->map.height;
    px = MINIMAP_X + (int)(game->player.pos_x * scale_x);
    py = MINIMAP_Y + (int)(game->player.pos_y * scale_y);
    i = -PLAYER_DOT_SIZE;
    while (i <= PLAYER_DOT_SIZE)
    {
        j = -PLAYER_DOT_SIZE;
        while (j <= PLAYER_DOT_SIZE)
        {
            draw_minimap_pixel(game, px + j, py + i, MINIMAP_PLAYER_COLOR);
            j++;
        }
        i++;
    }
}

void	render_minimap(t_game *game)
{
    render_map(game);
    render_player(game);
}