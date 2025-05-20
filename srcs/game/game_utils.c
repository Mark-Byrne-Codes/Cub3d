#include "../../include/cub3d.h"

uint32_t	create_rgba(t_color color)
{
	return (((uint32_t)color.r << 24) | ((uint32_t)color.g << 16)
		| ((uint32_t)color.b << 8) | 0xFF);
}

int	set_player_dir(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = -0.66;
	}
	else if (dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = 0.66;
	}
	else if (dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_y = -0.66;
	}
	else if (dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_y = 0.66;
	}
	return (0);
}

void	clean_exit(t_game *game, char *msg)
{
	if (!game)
		exit(0);
	free_map(game);
	if (msg)
		ft_putstr_fd(msg, 2);
	if (game->mlx)
	{
		if (game->img)
			mlx_delete_image(game->mlx, game->img);
		if (game->graphics.north)
			mlx_delete_image(game->mlx, game->graphics.north);
		if (game->graphics.south)
			mlx_delete_image(game->mlx, game->graphics.south);
		if (game->graphics.west)
			mlx_delete_image(game->mlx, game->graphics.west);
		if (game->graphics.east)
			mlx_delete_image(game->mlx, game->graphics.east);
		mlx_terminate(game->mlx);
	}
	free(game);
	exit(0);
}
