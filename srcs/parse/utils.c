/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahamdan <hahamdan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:04:09 by hahamdan          #+#    #+#             */
/*   Updated: 2025/05/25 17:04:14 by hahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * converts a string to an RGB value (0-255). 
 * @param str A string contains numeric value.
 * @return The RGB value on success, or -1 if invalid.
 */
int	convert_rgb(char *str)
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

/**
 * Trims characters from the beginning and end of a string
 * and then splits the string into an array of substrings
 based on the delimiter that was given.
 @param map_line A line from the map.
 @return An array of strings, or NULL on error.
 */
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

void	set_color(t_game *game, t_color rgb, char c)
{
	if (c == 'F')
	{
		game->graphics.floor_color = rgb;
		game->map.floor_set = true;
	}
	else
	{
		game->graphics.ceiling_color = rgb;
		game->map.ceiling_set = true;
	}
}

int	ft_comma(char *str)
{
	int	i;
	int	comma;

	i = -1;
	comma = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == ',')
			comma++;
	}
	if (comma > 2)
		return (EXIT_FAILURE);
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
