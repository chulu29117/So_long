/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_solvable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:43:56 by clu               #+#    #+#             */
/*   Updated: 2025/02/21 11:15:17 by clu              ###   ########.fr       */
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

// Flood fill algorithm to check if the map is solvable
static void	flood_map(t_game *game, int y, int x)
{
	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
		return ;
	if (game->map[y][x] == WALL || game->map[y][x] == VISITED)
		return ;
	if (game->map[y][x] == COLLECT)
		game->collected++;
	if (game->map[y][x] == EXIT)
		game->finished = TRUE;
	game->map[y][x] = 'F';
	flood_map(game, y - 1, x);
	flood_map(game, y + 1, x);
	flood_map(game, y, x - 1);
	flood_map(game, y, x + 1);
}



// Check if the map is solvable
int	solvable(t_game *game)
{
	game->map_copy = copy_map(game->map, game->map_height);
	if (!game->map_copy)
		exit_error("Failed to copy map");
	set_player_start(game);
	game->collected = 0;
	game->finished = FALSE;
	flood_map(game, game->player.y, game->player.x);
	if (game->collected != game->total_collected || !game->finished)
	{
		free_map(game->map_copy);
		return (FALSE);
	}
	free_map(game->map_copy);
	return (TRUE);
}
