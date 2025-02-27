/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:32:18 by clu               #+#    #+#             */
/*   Updated: 2025/02/27 17:38:22 by clu              ###   ########.fr       */
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
		ft_printf("Error\nInvalid map: Map is not rectangular!\n");
		return (FALSE);
	}
	if (!check_walls(game))
	{
		ft_printf("Error\nInvalid map: Map is not closed/surrounded by wall!");
		return (FALSE);
	}
	if (!check_elements(game))
		return (FALSE);
	if (!check_solvable(game))
	{
		ft_printf("Error\nMap is not solvable!");
		return (FALSE);
	}
	return (TRUE);
}
