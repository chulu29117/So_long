/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:39:27 by clu               #+#    #+#             */
/*   Updated: 2025/02/19 12:56:03 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*get_map_path(char *arg)
{
	char	*path;

	if (!ft_strchr(arg, '/'))
		path = ft_strjoin("maps/", arg);
	else
		path = ft_strdup(arg);
	return (path);
}

static int	init_game(t_game *game)
{
	game->move_count = 0;
	game->mlx = mlx_init(game->map_width, game->map_height, "so_long", true);
	if (!game->mlx)
	{
		free_game(game);
		exit_error("Failed to initialize mlx game");
	}
	get_textures(game);
	get_images(game);
	draw_map(game, game->img);
	mlx_image_to_window(game->mlx, game->img->player,
		game->player.x * TILE_SIZE, game->player.y * TILE_SIZE);
	mlx_key_hook(game->mlx, keyhook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_game(game);
	return (true);
}

static int	start_game(t_game *game, char *map_path)
{
	parse_map(map_path, game);
	free(map_path);
	if (!validate_map(game))
	{
		free_game(game);
		exit_error("Invalid map");
	}
	size_map(game, game->map);
	set_player_start(game);
	count_collect(game);
	ft_printf("Number of Pikachus to catch: %d\n", game->total_collected);
	game->collected = 0;
	if (!init_game(game))
	{
		free_game(game);
		exit_error("Failed to initialize game");
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_game	game;
	char	*map_path;

	if (argc != 2)
		exit_error("Usage: ./so_long <map.ber>");
	map_path = get_map_path(argv[1]);
	if (!start_game(&game, map_path))
		exit_error("Failed to start game");
	return (EXIT_SUCCESS);
}
