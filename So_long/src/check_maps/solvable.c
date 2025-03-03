/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solvable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:35:21 by clu               #+#    #+#             */
/*   Updated: 2025/03/03 15:24:09 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**copy_map(char **map, int height);
static void	flood_fill_collectibles(t_game *game, char **map, int y, int x);
static void	flood_fill_exit(t_game *game, char **map, int y, int x);

// Check if the map is solvable
	// Flood fill the player's position and check collectibles
	// Flood fill the player's position and check the exit
	// If the collectibles and exit are found, return true
int	check_solvable(t_game *game)
{
	char	**map_copy1;
	char	**map_copy2;
	int		collect_ok;
	int		exit_ok;

	game->collect_found = 0;
	map_copy1 = copy_map(game->map, game->map_rows);
	flood_fill_collectibles(game, map_copy1, game->player.y, game->player.x);
	free_map(map_copy1);
	collect_ok = (game->collect_found == game->total_collected);
	game->exit_found = FALSE;
	map_copy2 = copy_map(game->map, game->map_rows);
	flood_fill_exit(game, map_copy2, game->player.y, game->player.x);
	free_map(map_copy2);
	exit_ok = game->exit_found;
	if (collect_ok && exit_ok)
		return (TRUE);
	return (FALSE);
}

// Copy the map to a new memory location
	// Loop through the map and copy each row
static char	**copy_map(char **map, int height)
{
	char	**dup_map;
	int		i;

	dup_map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!dup_map)
	{
		free_map(map);
		exit_error("Failed to allocate memory for map copy");
	}
	i = 0;
	while (i < height)
	{
		dup_map[i] = ft_strdup(map[i]);
		if (!dup_map[i])
		{
			while (i--)
				free(dup_map[i]);
			free(dup_map);
			free_map(map);
			exit_error("Failed to allocate memory for map copy");
		}
		i++;
	}
	dup_map[height] = NULL;
	return (dup_map);
}

// Flood fill the map to find collectibles
	// If the position is out of bounds, return
	// If the position is a wall, exit, or visited, return
	// If the position is a collectible, increment the collectible count
	// Mark the position as visited
	// Recursively flood fill the position in all directions
static void	flood_fill_collectibles(t_game *game, char **map, int y, int x)
{
	if (x < 0 || y < 0 || x >= game->map_cols || y >= game->map_rows)
		return ;
	if (map[y][x] == WALL || map[y][x] == EXIT || map[y][x] == VISITED)
		return ;
	if (map[y][x] == COLLECT)
		game->collect_found++;
	map[y][x] = VISITED;
	flood_fill_collectibles(game, map, y + 1, x);
	flood_fill_collectibles(game, map, y - 1, x);
	flood_fill_collectibles(game, map, y, x + 1);
	flood_fill_collectibles(game, map, y, x - 1);
}

// Flood fill the map to find the exit
	// If the position is out of bounds, return
	// If the position is a wall or visited, return
	// If the position is an exit, set the exit found flag
	// Mark the position as visited
	// Recursively flood fill the position in all directions
static void	flood_fill_exit(t_game *game, char **map, int y, int x)
{
	if (x < 0 || y < 0 || x >= game->map_cols || y >= game->map_rows)
		return ;
	if (map[y][x] == WALL || map[y][x] == VISITED)
		return ;
	if (map[y][x] == EXIT)
		game->exit_found = TRUE;
	map[y][x] = VISITED;
	flood_fill_exit(game, map, y + 1, x);
	flood_fill_exit(game, map, y - 1, x);
	flood_fill_exit(game, map, y, x + 1);
	flood_fill_exit(game, map, y, x - 1);
}
