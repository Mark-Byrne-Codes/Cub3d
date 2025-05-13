#include "../../include/cub3d.h"

int		check_map_element(char *element, char **arr);
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

void free_map(t_game *game)
{
    int	i;

    if (!game)
		return;
	if (game->map.map_grid) 
	{
		i = -1;
		while (game->map.map_grid[++i])
			free(game->map.map_grid[i]);
		free(game->map.map_grid);
		game->map.map_grid = NULL;
	}
	if (game->map.map_data)
	{
		i = -1;
		while (game->map.map_data[++i]) 
			free(game->map.map_data[i]);
		free(game->map.map_data);
		game->map.map_data = NULL;
	}
	free(game->map.north_texture);
	free(game->map.south_texture);
	free(game->map.west_texture);
	free(game->map.east_texture);
	game->map.north_texture = NULL;
	game->map.south_texture = NULL;
	game->map.west_texture = NULL;
	game->map.east_texture = NULL;
	// free(game);
	// game = NULL;
	}

int	get_height(t_game *game, char *filename)
{
	char	*gnl;
	int		i;

	game->map.fd = open(filename, O_RDONLY);
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
	// game->map.width = 0;
	game->map.height = 0;
	game->map.player_x = 0;
	game->map.player_y = 0;
	game->map.floor_set = 0;
	game->map.ceiling_set = 0;
	game->map.start_dir = '\0';
	game->map.map_grid = NULL;
	game->map.map_data = NULL;
	// game->map.file_path = NULL;
	game->map.north_texture = NULL;
	game->map.south_texture = NULL;
	game->map.west_texture = NULL;
	game->map.east_texture = NULL;
}

int	allocate_map_grid(t_game *game, int height)
{
	int		i;
	char	*gnl;

	i = -1;
	gnl = get_next_line(game->map.fd);
	if (!gnl)
		return (EXIT_FAILURE);
	while (gnl && ++i < height)
	{
		game->map.map_grid[i] = ft_strdup(gnl);
		if (!game->map.map_grid[i])
			return (free(gnl), EXIT_FAILURE);
		free(gnl);
		gnl = get_next_line(game->map.fd);
	}
	if (gnl)
		free(gnl);
	return (EXIT_SUCCESS);
}

int	read_map(t_game *game, char *argv)
{
	int height;

	init_map_struct(game);
	// game->map.file_path = argv;
	height = get_height(game, argv);
	if (height == -1)
		return (return_error(game, "Error:  Invalid map"));
	game->map.map_grid = ft_calloc(height + 1, sizeof(char *));
	if (!game->map.map_grid)
		return (return_error(game, "Error: Failed to allocate map grid"));
	game->map.fd = open(argv, O_RDONLY);
	if (game->map.fd == -1)
		return (return_error(game, "Error: Failed to open map file"));
	if (allocate_map_grid(game, height))
		return (return_error(game, "Error: Failed to allocate map row"));
	int i = 0;
	printf("\033[1;33m########## Map file config ###############\033[0m\n\n");
	while (i < height)
	{
		printf("%s", game->map.map_grid[i]);
		i++;
	}
	printf("\n\n\033[1;33m##########ERROR###############\033[0m\n");
	close(game->map.fd);
	return (EXIT_SUCCESS);
}

void	free_grid(char **split)
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
void configuration_format(int err);

int	handle_error(char *line, int err, char *element)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (err == ERR_EXT)
		ft_putstr_fd("Invalid texture file: Expected: <.png> file: ",
			STDERR_FILENO);
	if (err == ERR_FILE)
		ft_putstr_fd("Cannot open texture file: ", STDERR_FILENO);
	if (err == ERR_CONFIG)
		return (ft_putstr_fd("Invalid map configuration\n", 2), 1);
	if (err == ERR_READ)
			ft_putstr_fd("Permission denied: Cannot read file: ", 2);
	if (err == NO_FILE)
			ft_putstr_fd("File does not exist: ", STDERR_FILENO);
	if (err == ERR_RGB || err == ERR_DUP || err == ERR_IS_DIR || err == NO_EXT)
	{
		if (err == ERR_RGB)
			ft_putstr_fd("Invalid color format: Expected R,G,B ([0-255]"
			" without spaces): ", STDERR_FILENO);
		else if (err == ERR_DUP)
			ft_putstr_fd("Duplicate definition of map element: ", 2);
		else if (err == ERR_IS_DIR)
			ft_putstr_fd("Path is a directory: ", STDERR_FILENO);
		else
			ft_putstr_fd("Missing texture path for ", STDERR_FILENO);
		ft_putstr_fd(element, STDERR_FILENO);
		if (err == NO_EXT)
			ft_putstr_fd(" \n", STDERR_FILENO);
		else
			ft_putchar_fd(' ', STDERR_FILENO);
	}
	if (line)
		ft_putendl_fd(line, STDERR_FILENO);
	return (EXIT_FAILURE);
}

int check_file_permissions(char *texture)
{
	const char	*extension;
	int 		fd;

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
	int err;

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

int	check_map_element(char *element, char **arr)
{
	if (ft_strcmp(element, "NO") != 0 && ft_strcmp(element, "SO") != 0
		&& ft_strcmp(element, "WE") != 0 && ft_strcmp(element, "EA") != 0
		&& ft_strcmp(element, "F") != 0 && ft_strcmp(element, "C") != 0)
	{
		if (element[0] == '1' || element[0] == '0' || element[0] == ' '
			|| element[0] == 'N' || element[0] == 'S'
			|| element[0] == 'W' || element[0] == 'E')
			return (MAP_LINE); // Special code for map lines
		return (ERR_CONFIG);
	}
	if (!arr[1])
		return (NO_EXT);
	if (arr[2])
		return (ERR_CONFIG);
	return (EXIT_SUCCESS);
}
void configuration_format(int err)
{
	(void)err;
	ft_putstr_fd("\033[1;33mRequired configuration format:\033[0m\n",
	STDERR_FILENO);
	ft_putstr_fd("NO path/to/north_texture.png\n", STDERR_FILENO);
	ft_putstr_fd("SO path/to/south_texture.png\n", STDERR_FILENO);
	ft_putstr_fd("WE path/to/west_texture.png\n", STDERR_FILENO);
	ft_putstr_fd("EA path/to/east_texture.png\n", STDERR_FILENO);
	ft_putstr_fd("F  0,0,0  (RGB values 0-255)\n", STDERR_FILENO);
	ft_putstr_fd("C  0,0,0  (RGB values 0-255)\n", STDERR_FILENO);
}

int check_required_config(t_game *game)
{
	if (!game->map.north_texture || !game->map.south_texture
		|| !game->map.west_texture || !game->map.east_texture
		|| !game->map.ceiling_set || !game->map.floor_set)
	{
		configuration_format(0);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int 	get_map_height(t_game *game, int i)
{
	int height;

	height = 0;
	while (game->map.map_grid[i] != NULL)
	{
		i++;
		height++;
	}
	return (height);
}

int  find_player(t_game *game);
int allocate_map_data(t_game *game, int i)
{
    int j;

    game->map.height = get_map_height(game, i);
    game->map.map_data = ft_calloc(game->map.height + 1, sizeof(char *));
    game->map.widths = ft_calloc(game->map.height, sizeof(int));
    if (!game->map.map_data || !game->map.widths)
        return (return_error(game, "Error: Failed to allocate map data"));
    j = 0;
    game->map.max_width = 0;
    while (game->map.map_grid[i] != NULL)
    {
        game->map.map_data[j] = ft_strtrim(game->map.map_grid[i], "\n");
        if (!game->map.map_data[j])
            return (return_error(game, "Error: Failed to allocate map row"));
        game->map.widths[j] = ft_strlen(game->map.map_data[j]);
        printf("map width: %d\n", game->map.widths[j]);
        if (game->map.widths[j] > game->map.max_width)
            game->map.max_width = game->map.widths[j];
        j++;
        i++;
    }
	game->map.width = game->map.max_width;
    printf("\n\033[1;33m########## Map data ###############\033[0m\n\n");
    i = -1;
    while (++i < game->map.height)
        printf("%s\n", game->map.map_data[i]);
    printf("\n\n");
    return (EXIT_SUCCESS);
}

int 	handle_map_error(int err)
{
	ft_putstr_fd("Error: Invalid map: ", STDERR_FILENO);
	if (err == MULTI_PLAYER)
		ft_putstr_fd("Multiple players found: "
		"Map must contain one of: N, S, E, W\n", STDERR_FILENO);
	if (err == NO_PLAYER)
		ft_putstr_fd("No player found: "
		"Map must contain one of: N, S, E, W\n", STDERR_FILENO);
	if (err == INVALID_CHAR)
		ft_putstr_fd("Found invalid character\n"
		"Allowed characters: 0, 1, N, S, W, E, space\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
// printf("\033[1;31mInvalid character '%c' at [%d][%d]\033[0m\n", c, i, j);
// printf("\033[1;32mPlayer validation successful!\033[0m\n");
int find_player(t_game *game)
{
    int        i;
    int        j;
    char    c;
    int        found;

    printf("\n\033[1;33m########## Player Validation ###############\033[0m\n");
    i = -1;
    found = 0;
    while (game->map.map_data[++i])
    {
        j = -1;
        while (game->map.map_data[i][++j])
        {
            c = game->map.map_data[i][j];
            if (!ft_strchr("01NSEW ", c))
                return (INVALID_CHAR);
            if (ft_strchr("NSEW", c))
            {
                found++;
                game->map.start_dir = c;
                game->map.player_x = j;
                game->map.player_y = i;
                if (found > 1)
                    return (MULTI_PLAYER);
            }
        }
    }
    if (found == 0)
        return (NO_PLAYER);
    printf("\033[1;32mPlayer validation successful!\033[0m\n");
    return (EXIT_SUCCESS);
}

int 	validate_map_data(t_game *game, int i)
{
	int err;

	if (allocate_map_data(game, i))
		return (EXIT_FAILURE);
	err = find_player(game);
	if (err)
		return (handle_map_error(err));
	return (EXIT_SUCCESS);
}
int process_configuration(t_game *game)
{
	int i;
	char **line;

	i = -1;
	while (game->map.map_grid[++i] != NULL)
	{
		line = trim_and_split(game->map.map_grid[i]);
		if (!line)
		{
			if (errno == ENOMEM)
				return (EXIT_FAILURE);
			i++;
			continue;
		}
		if (check_map_element(line[0], line) == MAP_LINE)
		{
			free_grid(line);
			break; 
		}
		if (load_config_element(game, line[0], line[1], line))
		    return (free_grid(line), EXIT_FAILURE);
		free_grid(line);
	}
	if (validate_map_data(game, i - 1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


int	validate_map_configuration(t_game *game)
{
	if (process_configuration(game) == MAP_LINE)
		return (EXIT_FAILURE);
	if (check_required_config(game))
		return(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}