/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:21:13 by clu               #+#    #+#             */
/*   Updated: 2025/02/14 20:47:28 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** read_file:
** Reads the entire contents of the file using get_next_line.
** Returns a dynamically allocated string containing the file's content.
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
	while ((line = get_next_line(fd)))
	{
		temp = content;
		content = ft_strjoin(temp, line);
		free(temp);
		free(line);
	}
	close(fd);
	return (content);
}

/*
** parse_map:
** Reads the map from the given file and fills the game->map structure.
** The map is stored as a NULL-terminated array of strings.
*/
void	parse_map(char *file, t_game *game)
{
	char	*file_content;

	file_content = read_file(file);
	if (!file_content || !file_content[0])
		exit_error("Empty map file");
	game->map.grid = ft_split(file_content, '\n');
	free(file_content);
	game->map.height = 0;
	while (game->map.grid[game->map.height])
		game->map.height++;
	if (game->map.height > 0)
		game->map.width = ft_strlen(game->map.grid[0]);
	else
		game->map.width = 0;
}

