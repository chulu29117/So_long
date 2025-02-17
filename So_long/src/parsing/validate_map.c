/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:32:18 by clu               #+#    #+#             */
/*   Updated: 2025/02/17 13:54:05 by clu              ###   ########.fr       */
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

// Ensure that the first and last rows consist of 1s
// First and last characters of each rows are also 1s
static int	check_walls(t_game *game)
{
	int	i;
	int	j;
	int	height;

	if (!game->map)
		return (FALSE);
	height = 0;
	while (game->map[height])
		height++;
	/* Check top row */
	i = 0;
	while (game->map[0][i])
	{
		if (game->map[0][i] != WALL)
			return (FALSE);
		i++;
	}
	/* Check bottom row */
	i = 0;
	while (game->map[height - 1][i])
	{
		if (game->map[height - 1][i] != WALL)
			return (FALSE);
		i++;
	}
	/* Check left and right borders */
	j = 0;
	while (j < height)
	{
		if (game->map[j][0] != WALL ||
			game->map[j][ft_strlen(game->map[j]) - 1] != WALL)
			return (FALSE);
		j++;
	}
	return (TRUE);
}

// Count the occurrences of the player (P), exit (E), and collectible (C).
// There must be exactly one P, exactly one E, and at least one C.
static int	check_elements(t_game *game)
{
	int	i;
	int	j;
	int	count_player;
	int	count_exit;
	int	count_collect;

	count_player = 0;
	count_exit = 0;
	count_collect = 0;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == PLAYER)
				count_player++;
			else if (game->map[i][j] == EXIT)
				count_exit++;
			else if (game->map[i][j] == COLLECT)
				count_collect++;
			j++;
		}
		i++;
	}
	if (count_player != 1 || count_exit != 1 || count_collect < 1)
		return (FALSE);
	return (TRUE);
}

// Checks the map for rectangularity, proper wall borders, and required elements. 
// Returns true if the map is valid; otherwise, prints an error
int	validate_map(t_game *game)
{
	if (!check_rectangle(game))
	{
		ft_printf("Error\nMap is not rectangular\n");
		return (false);
	}
	if (!check_walls(game))
	{
		ft_printf("Error\nMap is not closed/surrounded by wall\n");
		return (false);
	}
	if (!check_elements(game))
	{
		ft_printf("Error\nMap must have 1 player, 1 exit," );
		ft_printf("and at least 1 collectible\n");
		return (false);
	}
	return (true);
}
