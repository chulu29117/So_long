/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:56:34 by clu               #+#    #+#             */
/*   Updated: 2025/03/03 15:19:42 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_char(t_game *game);
static int	check_p_and_e(t_game *game, int *count_player, int *count_exit);
static int	check_collectibles(t_game *game, int *count_collect);

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
	if (!check_char(game))
	{
		ft_printf("Error\nInvalid map: Map contains invalid characters!\n");
		return (FALSE);
	}
	if (!check_p_and_e(game, &count_player, &count_exit))
	{
		ft_printf("Error\nInvalid map: Map must have 1 player and 1 exit!\n");
		return (FALSE);
	}
	if (!check_collectibles(game, &count_collect))
	{
		ft_printf("Error\nInvalid map: Map must have at least 1 collectible!\n");
		return (FALSE);
	}
	return (TRUE);
}

// Check if the map contains only valid characters
static int	check_char(t_game *game)
{
	int		i;
	int		j;
	char	*valid_chars;

	i = 0;
	valid_chars = "01CEP";
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!ft_strchr(valid_chars, game->map[i][j]))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

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
		return (TRUE);
	return (FALSE);
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
