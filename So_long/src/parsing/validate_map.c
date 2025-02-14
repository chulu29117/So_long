/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:32:18 by clu               #+#    #+#             */
/*   Updated: 2025/02/14 21:12:47 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Ensure that every row in the map has the same length.
static bool	check_rectangle(t_map *map)
{
	int		i;
	size_t	len;

	if (!map->grid || map->height <= 0)
		return (false);
	len = ft_strlen(map->grid[0]);
	i = 0;
	while (map->grid[i])
	{
		if (ft_strlen(map->grid[i]) != len)
			return (false);
		i++;
	}
	return (true);
}

// Ensure that the first and last rows consist of 1s
// First and last characters of each rows are also 1s
static bool	check_walls(t_map *map)
{
	int	i;
	int	j;

	/* Check top row */
	i = 0;
	while (map->grid[0][i])
	{
		if (map->grid[0][i] != '1')
			return (false);
		i++;
	}
	/* Check bottom row */
	i = 0;
	while (map->grid[map->height - 1][i])
	{
		if (map->grid[map->height - 1][i] != '1')
			return (false);
		i++;
	}
	/* Check left and right borders */
	j = 0;
	while (j < map->height)
	{
		if (map->grid[j][0] != '1'
			|| map->grid[j][ft_strlen(map->grid[j]) - 1] != '1')
			return (false);
		j++;
	}
	return (true);
}

// Count the occurrences of the player (P), exit (E), and collectible (C).
// There must be exactly one P, exactly one E, and at least one C.
static bool check_elements(t_map *map)
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
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'P')
				count_player++;
			else if (map->grid[i][j] == 'E')
				count_exit++;
			else if (map->grid[i][j] == 'C')
				count_collect++;
			j++;
		}
		i++;
	}
	if (count_player != 1 || count_exit != 1 || count_collect < 1)
		return (false);
	return (true);
}

// Checks the map for rectangularity, proper wall borders, and required elements. 
// Returns true if the map is valid; otherwise, prints an error
bool	validate_map(t_map *map)
{
	if (!check_rectangle(map))
	{
		ft_printf("Error\nMap is not rectangular\n");
		return (false);
	}
	if (!check_walls(map))
	{
		ft_printf("Error\nMap is not closed/surrounded by wall\n");
		return (false);
	}
	if (!check_elements(map))
	{
		ft_printf("Error\nMap must have 1 player, 1 exit," );
		ft_printf("and at least 1 collectible\n");
		return (false);
	}
	return (true);
}
