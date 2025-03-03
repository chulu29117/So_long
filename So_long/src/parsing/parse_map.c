/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:21:13 by clu               #+#    #+#             */
/*   Updated: 2025/03/03 12:16:51 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	process_lines(char **content, char *line, int fd);
static char	*read_file(char *file);

// Reads the map from the given file and fills the game->map structure.
	// The map is stored as a NULL-terminated array of strings.
void	parse_map(char *file, t_game *game)
{
	char	*file_content;
	char	**map;

	file_content = read_file(file);
	if (!file_content || !file_content[0])
	{
		free(file_content);
		free_parsing(game, file, "Empty map file");
	}
	if (ft_strnstr(file_content, "\n\n", ft_strlen(file_content)))
	{
		free(file_content);
		free_parsing(game, file, "Empty line in the map");
	}
	map = ft_split(file_content, '\n');
	if (!map)
	{
		free(file_content);
		free_parsing(game, file, "Failed to allocate memory for map");
	}
	free(file_content);
	game->map = map;
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
		free(file);
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

// Set the player's starting position
int	set_player_start(t_game *game)
{
	int	row;
	int	col;

	if (!game->map)
		exit_error("No map found");
	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == 'P')
			{
				game->player.x = col;
				game->player.y = row;
				return (TRUE);
			}
			col++;
		}
		row++;
	}
	free_game(game);
	ft_printf("Error\nNo player start ('P') found in map\n");
	return (FALSE);
}
