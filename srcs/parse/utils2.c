#include "../../include/cub3d.h"

/**
 * converts a string to an RGB value (0-255). 
 * @param str A string contains numeric value.
 * @return The RGB value on success, or -1 if invalid.
 */
int	assign_rgb(char *str)
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
