/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:21:13 by clu               #+#    #+#             */
/*   Updated: 2025/02/17 13:58:57 by clu              ###   ########.fr       */
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
	int		height;
	int		width;

	file_content = read_file(file);
	ft_printf("File content read:\n%s\n", file_content);
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

void	set_player_start(t_game *game)
{
	int	row;
	int	col;

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
				return ;
			}
			col++;
		}
		row++;
	}
	exit_error("No player start ('P') found in map");
}
