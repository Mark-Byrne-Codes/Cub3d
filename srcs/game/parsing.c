#include "../../include/cub3d.h"

void	free_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	return_error(t_game *game, char *msg)
{
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	if (game)
		free_map(game);
	if (game->map.fd >= 0)
	{
		free_gnl(game->map.fd);
		close(game->map.fd);
	}
	return (EXIT_FAILURE);
}

void	free_map(t_game *game)
{
	int	i;

	if (!game || !game->map.map_grid || !game->map.height)
		return ;
	i = 0;
	while (i < game->map.height)
	{
		if (game->map.map_grid[i])
			free(game->map.map_grid[i]);
		i++;
	}
	free(game->map.map_grid);
	game->map.map_grid = NULL;
	free(game->map.north_texture);
	game->map.north_texture = NULL;
	free(game->map.south_texture);
	game->map.south_texture = NULL;
	free(game->map.west_texture);
	game->map.west_texture = NULL;
	free(game->map.east_texture);
	game->map.east_texture = NULL;
}

int	get_height(t_game *game)
{
	char	*gnl;
	int		i;

	game->map.fd = open(game->map.file_path, O_RDONLY);
	if (game->map.fd == -1)
		return (-1);
	gnl = get_next_line(game->map.fd);
	if (!gnl)
		return (-1);
	i = 0;
	while (gnl != NULL && *gnl != '\0')
	{
		i++;
		free(gnl);
		gnl = get_next_line(game->map.fd);
	}
	if (i <= 0)
		return (-1);
	close(game->map.fd);
	return (i);
}

void	init_map_struct(t_game *game)
{
	game->map.fd = -1;
	game->map.width = 0;
	game->map.height = 0;
	game->map.floor_set = 0;
	game->map.ceiling_set = 0;
	game->map.start_dir = '\0';
	game->map.map_grid = NULL;
	game->map.file_path = NULL;
	game->map.north_texture = NULL;
	game->map.south_texture = NULL;
	game->map.west_texture = NULL;
	game->map.east_texture = NULL;
}
int	load_map(t_game *game, char *gnl, int i)
{
	game->map.width = ft_strlen(gnl);
	game->map.map_grid[i] = ft_calloc(game->map.width + 1, sizeof(char));
	if (!game->map.map_grid[i])
		return (free(gnl), EXIT_FAILURE);
	if (game->map.map_grid[i])
	{
		free(game->map.map_grid[i]);
		game->map.map_grid[i] = ft_strdup(gnl);
		if (!game->map.map_grid[i])
			return (free(gnl), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
int	allocate_map_grid(t_game *game)
{
	int		i;
	char	*gnl;

	i = -1;
	gnl = get_next_line(game->map.fd);
	if (!gnl)
		return (EXIT_FAILURE);
	while (gnl && ++i < game->map.height)
	{
		if (load_map(game, gnl, i))
			return (EXIT_FAILURE);
		free(gnl);
		gnl = get_next_line(game->map.fd);
	}
	if (gnl)
		free(gnl);
	return (EXIT_SUCCESS);
}

int	read_map(t_game *game, char *argv)
{
	init_map_struct(game);
	game->map.file_path = argv;
	game->map.height = get_height(game);
	if (game->map.height == -1)
		return (return_error(game, "Error:  Invalid map"));
	game->map.map_grid = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.map_grid)
		return (return_error(game, "Error: Failed to allocate map grid"));
	game->map.fd = open(game->map.file_path, O_RDONLY);
	if (game->map.fd == -1)
		return (return_error(game, "Error: Failed to open map file"));
	if (allocate_map_grid(game))
		return (return_error(game, "Error: Failed to allocate map row"));
	// int i = 0;
	// while (i < game->map.height)
	// {
	// 	printf("%s", game->map.map_grid[i]);
	// 	i++;
	// }
	printf("\n");
	close(game->map.fd);
	return (EXIT_SUCCESS);
}

void	free_array(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
}

int	check_texture(t_game *game, char *texture, char *direction)
{
	const char	*extension;

	if (!texture || !direction)
		return (EXIT_FAILURE);
	extension = ft_strrchr(texture, '.');
	if (!extension)
		return (EXIT_FAILURE);
	if ((extension && ft_strcmp(extension, ".png") != 0))
		return (EXIT_FAILURE);
	if (ft_strcmp(direction, "NO") == 0)
		game->map.north_texture = ft_strdup(texture);
	if (ft_strcmp(direction, "SO") == 0)
		game->map.south_texture = ft_strdup(texture);
	if (ft_strcmp(direction, "WE") == 0)
		game->map.west_texture = ft_strdup(texture);
	if (ft_strcmp(direction, "EA") == 0)
		game->map.east_texture = ft_strdup(texture);
	return (EXIT_SUCCESS);
}

int	check_rgb(char *str)
{
	int	color;

	color = ft_atoi(str);
	if (color < 0 || color > 255)
		return (-1);
	return (color);
}

int	check_color(t_game *game, char *color, char c)
{
	t_color	rgb;
	char	**rgb_format;

	if (!color)
		return (EXIT_FAILURE);
	rgb_format = ft_split(color, ',');
	if (!rgb_format || !rgb_format[0] || !rgb_format[1] || !rgb_format[2])
		return (EXIT_FAILURE);
	rgb.r = check_rgb(rgb_format[0]);
	rgb.g = check_rgb(rgb_format[1]);
	rgb.b = check_rgb(rgb_format[2]);
	if (rgb.r == -1 || rgb.g == -1 || rgb.b == -1)
		return (free_array(rgb_format), EXIT_FAILURE);
	if (c == 'F')
	{
		game->graphics.floor_color = rgb;
		game->map.floor_set = 1;
	}
	else
	{
		game->graphics.ceiling_color = rgb;
		game->map.ceiling_set = 1;
	}
	free_array(rgb_format);
	return (EXIT_SUCCESS);
}

int	load_elements(t_game *game, char *element, char *line)
{
	if (ft_strcmp(element, "NO") == 0 || ft_strcmp(element, "SO") == 0
		|| ft_strcmp(element, "WE") == 0 || ft_strcmp(element, "EA") == 0)
	{
		if (check_texture(game, line, element))
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(element, "F") == 0 || ft_strcmp(element, "C") == 0)
	{
		if (check_color(game, line, element[0]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	**trim_and_split(char *map_line)
{
	char	*trim;
	char	**line;

	trim = ft_strtrim(map_line, "\n");
	if (!trim)
		return (NULL);
	if (!trim[0])
		return (free(trim), EMPTY_LINE);
	line = ft_split(trim, ' ');
	free(trim);
	if (!line)
		return (NULL);
	return (line);
}
int	check_duplication(t_game *game, const char *identifier)
{
	if (ft_strcmp(identifier, "NO") == 0 && game->map.north_texture)
		return (EXIT_FAILURE);
	if (ft_strcmp(identifier, "SO") == 0 && game->map.south_texture)
		return (EXIT_FAILURE);
	if (ft_strcmp(identifier, "WE") == 0 && game->map.west_texture)
		return (EXIT_FAILURE);
	if (ft_strcmp(identifier, "EA") == 0 && game->map.east_texture)
		return (EXIT_FAILURE);
	if (ft_strcmp(identifier, "F") == 0 && game->map.floor_set)
		return (EXIT_FAILURE);
	if (ft_strcmp(identifier, "C") == 0 && game->map.ceiling_set)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
int	validate_map(t_game *game)
{
	int		i;
	char	**line;

	i = 0;
	while (game->map.map_grid[i] != NULL)
	{
		line = trim_and_split(game->map.map_grid[i]);
		if (!line)
			return (EXIT_FAILURE);
		if (line == EMPTY_LINE)
			break ;
		if (!((ft_strcmp(line[0], "NO") == 0 || ft_strcmp(line[0], "SO") == 0
			|| ft_strcmp(line[0], "WE") == 0 || ft_strcmp(line[0],"EA") == 0 
			|| ft_strcmp(line[0], "F") == 0|| ft_strcmp(line[0], "C") == 0)
			&& line[1] && !line[2]))
			return (free_array(line), EXIT_FAILURE);
		if (check_duplication(game, line[0]))
			return (free_array(line), EXIT_FAILURE);
		if (load_elements(game, line[0], line[1]))
			return (free_array(line), EXIT_FAILURE);
		free_array(line);
		i++;
	}
	return (EXIT_SUCCESS);
}
