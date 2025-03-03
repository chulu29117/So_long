/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:05:09 by clu               #+#    #+#             */
/*   Updated: 2025/03/03 15:25:39 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Set the player's starting position
	// Loop through the map and find the player's position
	// Set the player's x and y coordinates
int	set_player_start(t_game *game)
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
				return (TRUE);
			}
			col++;
		}
		row++;
	}
	ft_printf("Error\nNo player start ('P') found in map\n");
	return (FALSE);
}

// Count the number of collectibles on the map
	// Store the total number of collectibles
void	count_collect(t_game *game)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == COLLECT)
				count++;
			j++;
		}
		i++;
	}
	game->total_collected = count;
}
