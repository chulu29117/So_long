/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:21:31 by clu               #+#    #+#             */
/*   Updated: 2025/02/14 22:17:55 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hook(void *param)
{
	t_game	*game;
	
	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player(game, 0, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player(game, 0, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_player(game, -1, 0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player(game, 1, 0);
}
