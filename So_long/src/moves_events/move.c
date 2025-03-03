/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:21:26 by clu               #+#    #+#             */
/*   Updated: 2025/03/03 16:42:15 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_move(t_game *game, int new_x, int new_y);
static void	pick_collect(t_game *game, int new_x, int new_y);
static void	player_pos(t_game *game, int new_x, int new_y);
static void	show_move_count(t_game *game);

// Move the player on the map
	// If the player moves to the exit, show a message
	// If the player moves to the exit without collecting all, show a message
void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player.x + dx;
	new_y = game->player.y + dy;
	if (!check_move(game, new_x, new_y))
		return ;
	if (game->map[new_y][new_x] == EXIT)
	{
		if (game->collected != game->total_collected)
		{
			ft_printf("\n**YOU SHALL NOT LEAVE BEFORE YOU CATCH EM ALL!**\n\n");
			return ;
		}
	}
	player_pos(game, new_x, new_y);
	if (game->map[new_y][new_x] == EXIT)
	{
		ft_printf("\n***** Congratulations! You're the Pikachu Master! *****\n");
		ft_printf("\n*** Total moves used: %i ***\n", game->move_count);
		ft_printf("\n**** Press ESC or ENTER to exit ****\n");
		game->finished = TRUE;
		mlx_image_to_window(game->mlx, game->img->exit,
			new_x * TILE_SIZE, new_y * TILE_SIZE);
	}
}

// Check if the player can move to the new position
	// If the new position is a wall or outside the map, return false
	// If the new position is a collectible, increment the collected count
static int	check_move(t_game *game, int new_x, int new_y)
{
	int		max_x;
	int		max_y;
	int		row;

	max_x = ft_strlen(game->map[0]);
	max_y = 0;
	row = 0;
	while (game->map[row])
	{
		max_y++;
		row++;
	}
	if (new_x < 0 || new_x >= max_x || new_y < 0
		|| new_y >= max_y)
		return (FALSE);
	if (game->map[new_y][new_x] == '1')
		return (FALSE);
	if (game->map[new_y][new_x] == COLLECT)
		pick_collect(game, new_x, new_y);
	return (TRUE);
}

static void	pick_collect(t_game *game, int new_x, int new_y)
{
	size_t	i;

	game->collected++;
	ft_printf("Pikachu caught: %d, %d to go!\n", game->collected,
		game->total_collected - game->collected);
	game->map[new_y][new_x] = FLOOR;
	i = 0;
	while (i < game->img->collectible->count)
	{
		if (game->img->collectible->instances[i].x == new_x * TILE_SIZE
			&& game->img->collectible->instances[i].y == new_y * TILE_SIZE)
		{
			game->img->collectible->instances[i].enabled = FALSE;
			break ;
		}
		i++;
	}	
}

// // Move the player on the map
static void	player_pos(t_game *game, int new_x, int new_y)
{
	game->player.x = new_x;
	game->player.y = new_y;
	game->move_count++;
	ft_printf("Moves: %i\n", game->move_count);
	game->img->player->instances[0].x = new_x * TILE_SIZE;
	game->img->player->instances[0].y = new_y * TILE_SIZE;
	show_move_count(game);
}

// Show move count on the game screen
static void	show_move_count(t_game *game)
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
	if (game->move_text)
		game->move_text->enabled = FALSE;
	game->move_text = mlx_put_string(game->mlx, show_moves, 10, 10);
	free(moves);
	free(show_moves);
}
