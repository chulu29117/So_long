/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:21:26 by clu               #+#    #+#             */
/*   Updated: 2025/02/18 14:06:06 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	show_move_count(t_game *game)
{
	char	*moves;
	char	*show_moves;

	moves = ft_itoa(game->move_count);
	if (!moves)
		exit_error("Failed to allocate memory for move count");
	show_moves = ft_strjoin("Moves: ", moves);
	if (!show_moves)
	{
		free(moves);
		exit_error("Failed to allocate memory to show move count");
	}
	mlx_put_string(game->mlx, show_moves, 10, 10);
	free(moves);
	free(show_moves);
}

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

void	move_player(t_game *game, int dx, int dy)
{
	int	old_tile_x;
	int	old_tile_y;
	int	new_tile_x;
	int	new_tile_y;
	int	max_tiles_x;
	int	max_tiles_y;
	int	row;

	// Save old tile coordinates
	old_tile_x = game->player.x;
	old_tile_y = game->player.y;
	// Calculate new position in tile coordinates
	new_tile_x = game->player.x + dx;
	new_tile_y = game->player.y + dy;
	// Compute maximum tiles in x and y
	max_tiles_x = ft_strlen(game->map[0]);
	max_tiles_y = 0;
	row = 0;
	while (game->map[row])
	{
		max_tiles_y++;
		row++;
	}
	// Check boundaries in terms of tile counts
	if (new_tile_x < 0 || new_tile_x >= max_tiles_x ||
		new_tile_y < 0 || new_tile_y >= max_tiles_y)
		return ;
	// Check for wall collision (assuming '1' represents a wall)
	if (game->map[new_tile_y][new_tile_x] == '1')
		return ;
	// Check for collectibles
	if (game->map[new_tile_y][new_tile_x] == COLLECT)
	{
		game->collected++;
		ft_printf("Pikachu caught: %d, %d to go!\n", game->collected,
			game->total_collected - game->collected);
		game->map[new_tile_y][new_tile_x] = COLLECTED;
	}
	// Check for exit
	if (game->map[new_tile_y][new_tile_x] == EXIT)
	{
		if (game->collected == game->total_collected)
		{
			ft_printf("Congratulations! You've caught em all!\n");
			mlx_close_window(game->mlx);
			return ;
		}
		else
		{
			ft_printf("YOU SHALL NOT LEAVE BEFORE YOU CATCH EM ALL!\n");
			return ;
		}
	}
	// Update player's logical position and move count.
	game->player.x = new_tile_x;
	game->player.y = new_tile_y;
	game->move_count++;
	ft_printf("MOVES: %i\n", game->move_count);
	// Update the player's image instance's position in pixels
	game->img->player->instances[game->player_instance].x = new_tile_x * TILE_SIZE;
	game->img->player->instances[game->player_instance].y = new_tile_y * TILE_SIZE;
	if (game->map[old_tile_y][old_tile_x] == COLLECTED)
	{
		game->map[old_tile_y][old_tile_x] = FLOOR;
		mlx_image_to_window(game->mlx, game->img->floor,
		old_tile_x * TILE_SIZE, old_tile_y * TILE_SIZE);
	}
	show_move_count(game);
}
