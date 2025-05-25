/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahamdan <hahamdan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:03:09 by hahamdan          #+#    #+#             */
/*   Updated: 2025/05/25 17:03:13 by hahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * Checks the permission and validity of the texture file.
 * @param texture Path to texture file. 
 * @return An error code that inidicates the status of
 * the texture file check.
 */
static int	check_file_permissions(char *texture)
{
	const char	*extension;
	int			fd;

	fd = open(texture, O_DIRECTORY);
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

/**
 * Validates and assign texture file for a given direction
 * (e.g., "NO", "SO", "WE", "EA").
 * @param game Game state struct.
 * @param texture Path to the texture file.
 * @param direction The texture identifier
 * @return 'EXIT_SUCCCES if the texture is assigned, or an error code
 * if the texture validation failed.
 */
static int	check_texture(t_game *game, char *texture, char *direction)
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

/**
 * Validates and assign a color in RGB format.
 * @param game Game state struct.
 * @param color A string represntng the color in RGB format (e.g., "255, 0, 0").
 * @param c A character identifier ('F' for floor, 'C' for ceiling).
 * @return 'ERR_RGB' if the color format is invalid, or 'EXIT_SUCCESS'
 * if the color is valid.
 */
static int	check_color(t_game *game, char *color, char c)
{
	t_color	rgb;
	char	**clr;

	if (!color)
		return (EXIT_FAILURE);
	if (ft_comma(color))
		return (ERR_RGB);
	clr = ft_split(color, ',');
	if (!clr || !clr[0] || !clr[1] || !clr[2])
		return (free_grid(clr), ERR_RGB);
	rgb.r = convert_rgb(clr[0]);
	rgb.g = convert_rgb(clr[1]);
	rgb.b = convert_rgb(clr[2]);
	if (rgb.r == -1 || rgb.g == -1 || rgb.b == -1)
		return (free_grid(clr), ERR_RGB);
	set_color(game, rgb, c);
	free_grid(clr);
	return (EXIT_SUCCESS);
}

/**
 * Checks if a set element is duplicated.
 * @param game Game state struct. 
 * @param identifier The element identifier. 
 * @return ERR_DUP if the element is duplicated, EXIT_SUCCESS if not.
 */
static int	check_duplication(t_game *game, const char *identifier)
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

/**
 *  Assigns elements to the game state after validation.
 * @param game Game state struct.
 * @param identifier The element identifier.
 * @param line The element value.
 * @param arr An array contains the element identifier and its value.
 * @return An error code if assigment failed, or 'EXIT_SUCCESS' if successful.
 */
int	assign_element(t_game *game, char *identifier, char *line, char **arr)
{
	t_error	err;

	err = validate_identifier(identifier, arr);
	if (err)
		return (config_error(line, err, identifier));
	err = check_duplication(game, identifier);
	if (err)
		return (config_error(line, err, identifier));
	if (ft_strcmp(identifier, "NO") == 0 || ft_strcmp(identifier, "SO") == 0
		|| ft_strcmp(identifier, "WE") == 0 || ft_strcmp(identifier, "EA") == 0)
	{
		err = check_texture(game, line, identifier);
		if (err)
			return (config_error(line, err, identifier));
	}
	if (ft_strcmp(identifier, "F") == 0 || ft_strcmp(identifier, "C") == 0)
	{
		err = check_color(game, line, identifier[0]);
		if (err)
			return (config_error(line, err, identifier));
	}
	return (EXIT_SUCCESS);
}
