/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:21:13 by clu               #+#    #+#             */
/*   Updated: 2025/03/03 16:54:25 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	process_lines(char **content, char *line, int fd);
static char	*read_file(char *file);
static int	trailing_empty_lines(const char *content);

// Reads the map from the given file and fills the game->map structure.
	// The map is stored as a NULL-terminated array of strings.
void	parse_map(char *map_file, t_game *game)
{
	char	*file_content;
	char	**map;

	file_content = read_file(map_file);
	if (!file_content || !file_content[0])
		free_file(file_content, "Empty map file");
	if (file_content[0] == '\n')
		free_file(file_content, "Empty line at the beginning of the map");
	if (ft_strnstr(file_content, "\n\n", ft_strlen(file_content)))
		free_file(file_content, "Empty line in middle of the map");
	if (trailing_empty_lines(file_content))
		free_file(file_content, "Empty lines at the end of the map");
	map = ft_split(file_content, '\n');
	if (!map)
		free_file(file_content, "Failed to allocate memory for map");
	free(file_content);
	game->map = map;
}

// Checks if the file content has empty lines at the end.
static int	trailing_empty_lines(const char *content)
{
	size_t	len;

	len = ft_strlen(content);
	if (content[len - 1] == '\n')
	{
		while (len > 0 && content[len - 1] == '\n')
			len--;
		while (len > 0)
		{
			if (content[len - 1] == '\n')
				return (1);
			len--;
		}
	}
	return (0);
}

// Process the lines of the file content.
	// If the line is empty, free the line, content, and close the file.
	// Otherwise, join the line to the content.
static void	process_lines(char **content, char *line, int fd)
{
	char	*temp;

	temp = *content;
	*content = ft_strjoin(temp, line);
	free(temp);
	free(line);
	if (!*content)
	{
		close(fd);
		exit_error("Failed to allocate memory for map content");
	}
}

// Reads the entire contents of the file using get_next_line.
	// Returns a dynamically allocated string containing the file's content.
static char	*read_file(char *file)
{
	int		fd;
	char	*content;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		exit_error("Failed to open map: check file path");
	}
	content = ft_strdup("");
	if (!content)
	{
		close(fd);
		exit_error("Failed to allocate memory for map content");
	}
	line = get_next_line(fd);
	while (line)
	{
		process_lines(&content, line, fd);
		line = get_next_line(fd);
	}
	close(fd);
	return (content);
}

// Getting the size of the map by counting the number of rows and columns.
	// The map width is the number of columns multiplied by the tile size.
	// The map height is the number of rows multiplied by the tile size.
void	size_map(t_game *game, char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	game->map_cols = ft_strlen(map[0]);
	game->map_rows = i;
	game->map_width = ft_strlen(map[0]) * TILE_SIZE;
	game->map_height = i * TILE_SIZE;
}
