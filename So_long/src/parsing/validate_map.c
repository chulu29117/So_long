/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:32:18 by clu               #+#    #+#             */
/*   Updated: 2025/02/18 15:56:46 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Checks the map for rectangularity, proper wall borders,
// and required elements. 
// Returns true if the map is valid; otherwise, prints an error
int	validate_map(t_game *game)
{
	if (!check_rectangle(game))
	{
		ft_printf("Error:\nMap is not rectangular\n");
		return (false);
	}
	if (!check_walls(game))
	{
		ft_printf("Error:\nMap is not closed/surrounded by wall\n");
		return (false);
	}
	if (!check_elements(game))
	{
		ft_printf("Error:\nMap must have 1 player, 1 exit," );
		ft_printf("and at least 1 collectible\n");
		return (false);
	}
	return (true);
}
