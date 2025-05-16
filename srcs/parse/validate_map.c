#include "../../include/cub3d.h"

int	get_map_height(t_game *game, int i)
{
	int	height;

	height = 0;
	while (game->map.map_grid[i] != NULL)
	{
		i++;
		height++;
	}
	return (height);
}

	// printf("\n\033[1;33m########## Map data ###############\033[0m\n\n");
	// i = -1;
	// while (++i < game->map.height)
	// {
	// 	j = 0;
	// 	while (j < (int)game->map.max_width)
	// 	{
	// 		if (game->map.map_data[i][j] == ' ')
	// 			printf("S");
	// 		else
	// 			printf("%c", game->map.map_data[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// }
void	fill_map_content(t_game *game, int start_index)
{
	int		i;
	int		j;
	char	*temp;

	i = start_index;
	j = -1;
	while (++j < game->map.height)
	{
		temp = ft_strtrim(game->map.map_grid[i], "\n");
		ft_memcpy(game->map.map_data[j], temp, ft_strlen(temp));
		free(temp);
		i++;
	}
}

int	create_empty_map(t_game *game, int start_index, int j)
{
	int		i;
	char	*temp;

	i = start_index - 1;
	game->map.height = get_map_height(game, start_index);
	while (game->map.map_grid[++i] && (i - start_index) < game->map.height)
	{
		temp = ft_strtrim(game->map.map_grid[i], "\n");
		if (temp && !*temp)
			return (free(temp), MAP_LINE);
		if ((int)ft_strlen(temp) > game->map.max_width)
			game->map.max_width = ft_strlen(temp);
		free(temp);
	}
	game->map.map_data = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.map_data)
		return (return_error(game, "Map allocation failed"));
	while (++j < game->map.height)
	{
		game->map.map_data[j] = ft_calloc(game->map.max_width + 1,
				sizeof(char));
		if (!game->map.map_data[j])
			return (return_error(game, "Row allocation failed"));
		ft_memset(game->map.map_data[j], ' ', game->map.max_width);
		game->map.map_data[j][game->map.max_width] = '\0';
	}
	fill_map_content(game, start_index);
	return (EXIT_SUCCESS);
}

char	**duplicate_map(t_game *game)
{
	char	**temp;
	int		i;

	temp = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < game->map.height)
	{
		temp[i] = ft_strdup(game->map.map_data[i]);
		if (!temp[i])
			return (NULL);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}
