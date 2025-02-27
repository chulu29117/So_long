/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:21:37 by clu               #+#    #+#             */
/*   Updated: 2025/02/19 11:52:35 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Free the memory allocated for the map grid
// Free each row and then the grid pointer
void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

// Free all dynamically allocated resources in the game
void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
		free_map(game->map);
	if (game->img)
	{
		free(game->img);
		game->img = NULL;
	}
	if (game->tex)
	{
		free(game->tex);
		game->tex = NULL;
	}
}
