/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:56:34 by clu               #+#    #+#             */
/*   Updated: 2025/02/19 11:47:28 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Count the occurrences of the player (P) and exit (E).
// There must be exactly one P and exactly one E.
static int	check_p_and_e(t_game *game, int *count_player, int *count_exit)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == PLAYER)
				(*count_player)++;
			else if (game->map[i][j] == EXIT)
				(*count_exit)++;
			j++;
		}
		i++;
	}
	if (*count_player == 1 && *count_exit == 1)
		return (true);
	return (false);
}

// Count the occurrences of collectibles (C).
// There must be at least one C.
static int	check_collectibles(t_game *game, int *count_collect)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == COLLECT)
				(*count_collect)++;
			j++;
		}
		i++;
	}
	return (*count_collect >= 1);
}

// Count the occurrences of the player (P), exit (E), and collectible (C).
// There must be exactly one P, exactly one E, and at least one C.
int	check_elements(t_game *game)
{
	int	count_player;
	int	count_exit;
	int	count_collect;

	count_player = 0;
	count_exit = 0;
	count_collect = 0;
	if (!check_p_and_e(game, &count_player, &count_exit))
		return (false);
	if (!check_collectibles(game, &count_collect))
		return (false);
	return (true);
}
