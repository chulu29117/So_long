/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:21:13 by clu               #+#    #+#             */
/*   Updated: 2025/02/19 12:03:15 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
Getting the size of the map by counting the number of rows and columns.
*/
void	size_map(t_game *game, char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	game->map_width = ft_strlen(map[0]) * TILE_SIZE;
	game->map_height = i * TILE_SIZE;
}

/* 
Reads the entire contents of the file using get_next_line.
Returns a dynamically allocated string containing the file's content.
*/
static char	*read_file(char *file)
{
	int		fd;
	char	*line;
	char	*content;
	char	*temp;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error("Could not open map file");
	content = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		temp = content;
		content = ft_strjoin(temp, line);
		free(temp);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (content);
}

/*
Reads the map from the given file and fills the game->map structure.
The map is stored as a NULL-terminated array of strings.
*/
void	parse_map(char *file, t_game *game)
{
	char	*file_content;
	int		height;
	int		width;

	file_content = read_file(file);
	ft_printf("Map file read:\n%s\n", file_content);
	if (!file_content || !file_content[0])
		exit_error("Empty map file");
	game->map = ft_split(file_content, '\n');
	free(file_content);
	height = 0;
	while (game->map[height])
		height++;
	if (height > 0)
		width = ft_strlen(game->map[0]);
	else
		width = 0;
	game->map_height = height;
	game->map_width = width;
	ft_printf("Map dimensions: %d x %d\n", width, height);
}
