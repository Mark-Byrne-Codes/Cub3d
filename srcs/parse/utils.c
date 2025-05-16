#include "../../include/cub3d.h"

int	check_rgb(char *str)
{
	int	color;
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (-1);
	}
	color = ft_atoi(str);
	if (color < 0 || color > 255)
		return (-1);
	return (color);
}

char	**trim_and_split(char *map_line)
{
	char	*trim;
	char	**line;

	trim = ft_strtrim(map_line, "\n");
	if (!trim)
		return (NULL);
	if (!trim[0])
		return (free(trim), NULL);
	line = ft_split(trim, ' ');
	free(trim);
	if (!line)
		return (NULL);
	if ((line && !line[0]))
		return (free_grid(line), NULL);
	return (line);
}

int	check_file_permissions(char *texture)
{
	const char	*extension;
	int			fd;

	fd = open(texture, __O_DIRECTORY);
	if (fd != -1)
		return (close(fd), ERR_IS_DIR);
	if (access(texture, F_OK) == -1)
		return (NO_FILE);
	if (access(texture, R_OK) == -1)
		return (ERR_READ);
	extension = ft_strrchr(texture, '.');
	if (!extension)
		return (ERR_EXT);
	if ((extension && ft_strcmp(extension, ".png") != 0))
		return (ERR_EXT);
	fd = open(texture, O_RDONLY);
	if (fd == -1)
		return (ERR_FILE);
	close(fd);
	return (EXIT_SUCCESS);
}

int	check_texture(t_game *game, char *texture, char *direction)
{
	int	err;

	err = check_file_permissions(texture);
	if (err)
		return (err);
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

int	check_color(t_game *game, char *color, char c)
{
	t_color	rgb;
	char	**rgb_format;

	if (!color)
		return (EXIT_FAILURE);
	rgb_format = ft_split(color, ',');
	if (!rgb_format || !rgb_format[0] || !rgb_format[1] || !rgb_format[2])
		return (free_grid(rgb_format), ERR_RGB);
	rgb.r = check_rgb(rgb_format[0]);
	rgb.g = check_rgb(rgb_format[1]);
	rgb.b = check_rgb(rgb_format[2]);
	if (rgb.r == -1 || rgb.g == -1 || rgb.b == -1)
		return (free_grid(rgb_format), ERR_RGB);
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
	free_grid(rgb_format);
	return (EXIT_SUCCESS);
}

int	check_duplication(t_game *game, const char *identifier)
{
	if (ft_strcmp(identifier, "NO") == 0 && game->map.north_texture)
		return (ERR_DUP);
	if (ft_strcmp(identifier, "SO") == 0 && game->map.south_texture)
		return (ERR_DUP);
	if (ft_strcmp(identifier, "WE") == 0 && game->map.west_texture)
		return (ERR_DUP);
	if (ft_strcmp(identifier, "EA") == 0 && game->map.east_texture)
		return (ERR_DUP);
	if (ft_strcmp(identifier, "F") == 0 && game->map.floor_set)
		return (ERR_DUP);
	if (ft_strcmp(identifier, "C") == 0 && game->map.ceiling_set)
		return (ERR_DUP);
	return (EXIT_SUCCESS);
}

int	load_config_element(t_game *game, char *element, char *line, char **arr)
{
	t_error	err;

	err = check_map_element(element, arr);
	if (err)
		return (handle_error(line, err, element));
	err = check_duplication(game, element);
	if (err)
		return (handle_error(line, err, element));
	if (ft_strcmp(element, "NO") == 0 || ft_strcmp(element, "SO") == 0
		|| ft_strcmp(element, "WE") == 0 || ft_strcmp(element, "EA") == 0)
	{
		err = check_texture(game, line, element);
		if (err)
			return (handle_error(line, err, element));
	}
	if (ft_strcmp(element, "F") == 0 || ft_strcmp(element, "C") == 0)
	{
		err = check_color(game, line, element[0]);
		if (err)
			return (handle_error(line, err, element));
	}
	return (EXIT_SUCCESS);
}
