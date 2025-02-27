/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:32:18 by clu               #+#    #+#             */
/*   Updated: 2025/02/27 13:14:55 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Ensure that every row in the map has the same length.
static int	check_rectangle(t_game *game)
{
	int		i;
	size_t	len;

	if (!game->map)
		return (FALSE);
	if (!game->map[0])
		return (FALSE);
	len = ft_strlen(game->map[0]);
	i = 0;
	while (game->map[i])
	{
		if (ft_strlen(game->map[i]) != len)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

// Check the first and last rows for walls.
static int	check_top_bot_walls(t_game *game)
{
	int		i;

	i = 0;
	while (game->map[0][i])
	{
		if (game->map[0][i] != WALL)
			return (FALSE);
		i++;
	}
	i = 0;
	while (game->map[game->map_rows - 1][i])
	{
		if (game->map[game->map_rows - 1][i] != WALL)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

// Ensure that the first and last rows consist of 1s
// First and last characters of each rows are also 1s
static int	check_walls(t_game *game)
{
	int	i;

	if (!game->map)
		return (FALSE);
	// height = 0;
	// while (game->map[height])
	// 	height++;
	i = 0;
	while (i < game->map_rows)
	{
		if (game->map[i][0] != WALL || game->map[i][game->map_cols - 1] != WALL)
			return (FALSE);
		i++;
	}
	if (check_top_bot_walls(game) == FALSE)
		return (FALSE);
	return (TRUE);
}

// Checks the map for rectangularity, proper wall borders,
// and required elements. 
// Returns true if the map is valid; otherwise, prints an error
int	validate_map(t_game *game)
{
	if (!check_rectangle(game))
	{
		free_game(game);
		exit_error("Map is not rectangular!");
	}
	if (!check_walls(game))
	{
		free_game(game);
		exit_error("Map is not closed/surrounded by wall!");
	}
	if (!check_elements(game))
	{
		free_game(game);
		exit_error("Invalid map!");
	}
	if (!check_solvable(game))
	{
		free_game(game);
		exit_error("Map is not solvable!");
	}
	return (TRUE);
}
