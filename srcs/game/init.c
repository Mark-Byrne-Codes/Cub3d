#include "../../../include/cub3d.h"

void init_player(t_game *game)
{
    game->player->pos.x = 0;
    game->player->pos.y = 0;
    game->player->dir.x = 0;
    game->player->dir.y = 0;
    game->player->plane.x = 0;
    game->player->plane.y = 0;
}



void init_map(t_game *game)
{
    game->map->map = NULL;
    game->map->width = 0;
    game->map->height = 0;
    game->map->start_dir = 'N';
    game->map->player_x = 0;
    game->map->player_y = 0;
}

void init_ray(t_game *game)
{
    game->ray->x = 0;
    game->ray->y = 0;
    game->ray->map_x = 0;
    game->ray->map_y = 0;
    game->ray->side_dist_x = 0;
    game->ray->side_dist_y = 0;
    game->ray->delta_dist_x = 0;
    game->ray->delta_dist_y = 0;
    game->ray->perp_wall_dist = 0;
    game->ray->step_x = 0;
    game->ray->step_y = 0;
    game->ray->side = 0;
    game->ray->hit = 0;
}