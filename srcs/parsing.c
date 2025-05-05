#include "cub3d.h"

void init_map(t_map *map)
{
	map->fd = -1;
	map->max_width = 0;
	map->max_height = 0;
	map->index = NULL;
	map->file_path = NULL;
}

int run_game(argv)
{
	t_map	map;

	init_map(&map);

	return (0);
}