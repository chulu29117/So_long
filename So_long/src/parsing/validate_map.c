/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:32:18 by clu               #+#    #+#             */
/*   Updated: 2025/02/21 10:41:28 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Ensure that every row in the map has the same length.
static int	check_rectangle(t_game *game)
{
	int		i;
	size_t	len;

	if (!game->map)
		return (false);
	if (!game->map[0])
		return (false);
	len = ft_strlen(game->map[0]);
	i = 0;
	while (game->map[i])
	{
		if (ft_strlen(game->map[i]) != len)
			return (false);
		i++;
	}
	return (true);
}

// Check the first and last rows for walls.
static int	check_top_bot_walls(t_game *game, int height)
{
	int		i;

	i = 0;
	while (game->map[0][i])
	{
		if (game->map[0][i] != WALL)
			return (false);
		i++;
	}
	i = 0;
	while (game->map[height - 1][i])
	{
		if (game->map[height - 1][i] != WALL)
			return (false);
		i++;
	}
	return (true);
}

// Ensure that the first and last rows consist of 1s
// First and last characters of each rows are also 1s
static int	check_walls(t_game *game)
{
	int	i;
	int	height;

	if (!game->map)
		return (FALSE);
	height = 0;
	while (game->map[height])
		height++;
	i = 0;
	while (game->map[0][i])
	{
		if (game->map[0][i] != WALL)
			return (FALSE);
		i++;
	}
	if (check_top_bot_walls(game, height) == FALSE)
		return (FALSE);
	return (TRUE);
}

// Checks the map for rectangularity, proper wall borders,
// and required elements. 
// Returns true if the map is valid; otherwise, prints an error
int	validate_map(t_game *game)
{
	if (!check_rectangle(game))
		exit_error("Map is not rectangular");
	if (!check_walls(game))
		exit_error("Map is not closed/surrounded by wall");
	if (!check_elements(game))
	{
		ft_printf("Error: Map must have 1 player, 1 exit and at ");
		ft_printf("least 1 collectible\n");
		exit(EXIT_FAILURE);
	}
	if (!solvable(game))
	{
		ft_printf("Error: Map is not solvable\n");
		exit(EXIT_FAILURE);
	}
	return (TRUE);
}

// Set the player's starting position
void	set_player_start(t_game *game)
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
				return ;
			}
			col++;
		}
		row++;
	}
	exit_error("No player start ('P') found in map");
}
