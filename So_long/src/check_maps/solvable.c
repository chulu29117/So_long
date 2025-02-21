/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solvable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:35:21 by clu               #+#    #+#             */
/*   Updated: 2025/02/21 12:15:19 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_solvable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:43:56 by clu               #+#    #+#             */
/*   Updated: 2025/02/21 11:33:35 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Check if the map is solvable
static char	**copy_map(char **map, int height)
{
	char	**dup_map;
	int		i;

	dup_map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!dup_map)
		exit_error("Failed to allocate memory for map copy");
	i = 0;
	while (i < height)
	{
		dup_map[i] = ft_strdup(map[i]);
		if (!dup_map[i])
		{
			while (i--)
				free(dup_map[i]);
			free(dup_map);
			exit_error("Failed to allocate memory for map copy");
		}
		i++;
	}
	dup_map[height] = NULL;
	return (dup_map);
}
