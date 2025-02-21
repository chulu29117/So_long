/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solvable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:35:21 by clu               #+#    #+#             */
/*   Updated: 2025/02/21 16:01:14 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Check if the map is solvable
static char	**copy_map(char **map, int height)
{
	char	**dup_map;
	int		i;

	dup_map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!dup_map)
		exit_error("Failed to allocate memory for map copy");
	i = 0;
	while (i < height)
	{
		dup_map[i] = ft_strdup(map[i]);
		if (!dup_map[i])
		{
			while (i--)
				free(dup_map[i]);
			free(dup_map);
			exit_error("Failed to allocate memory for map copy");
		}
		i++;
	}
	dup_map[height] = NULL;
	return (dup_map);
}

static void	flood_fill(t_game *game, char **map, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map_cols || y >= game->map_rows)
		return ;
	if (map[y][x] == WALL || map[y][x] == VISITED)
		return ;
	if (map[y][x] == COLLECT)
		game->collect_found++;
	map[y][x] = VISITED;
	flood_fill(game, map, x + 1, y);
	flood_fill(game, map, x - 1, y);
	flood_fill(game, map, x, y + 1);
	flood_fill(game, map, x, y - 1);
}

int	check_solvable(t_game *game)
{
	int	i;
	int	j;

	game->map_copy = copy_map(game->map, game->map_rows);
	set_player_start(game);
	i = 0;
	while (i < game->map_rows)
	{
		j = 0;
		while (j < game->map_cols)
		{
			if (game->map_copy[i][j] == EXIT)
				game->map_copy[i][j] = WALL;
			j++;
		}
		i++;
	}
	set_player_start(game);
	flood_fill(game, game->map_copy, game->player.x, game->player.y);
	
	free_map(game->map_copy);
	return (TRUE);
}
