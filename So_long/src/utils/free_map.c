/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:21:37 by clu               #+#    #+#             */
/*   Updated: 2025/02/17 15:39:24 by clu              ###   ########.fr       */
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
	while (map[i++])
		free(map[i]);
	free(map);
}

// Free all dynamically allocated resources in the game
void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_map(game->map);
}
