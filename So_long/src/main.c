/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:39:27 by clu               #+#    #+#             */
/*   Updated: 2025/02/18 19:23:55 by clu              ###   ########.fr       */
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
		return (false);
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
		ft_printf("Error\nInvalid map\n");
		free_game(game);
		return (EXIT_FAILURE);
	}
	size_map(game, game->map);
	set_player_start(game);
	count_collect(game);
	ft_printf("Number of Pikachus to catch: %d\n", game->total_collected);
	game->collected = 0;
	if (!init_game(game))
	{
		ft_printf("Error\nFailed to initialize game\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	game;
	char	*map_path;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map.ber>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	map_path = get_map_path(argv[1]);
	if (start_game(&game, map_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
