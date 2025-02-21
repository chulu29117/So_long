/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:39:27 by clu               #+#    #+#             */
/*   Updated: 2025/02/21 10:45:13 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Get the path of the map file
// If the map file is in the maps directory, return the path
// Otherwise, return the path with the maps directory prepended
static char	*get_map_path(char *arg)
{
	char	*path;

	if (!ft_strchr(arg, '/'))
		path = ft_strjoin("maps/", arg);
	else
		path = ft_strdup(arg);
	return (path);
}

// Initialize the game
// Initialize the mlx window
// Load the textures->Load the images->Draw the map
// Draw the player at the player's starting position
// Set the keyhook to the keyhook function
// Start the mlx loop
static int	init_game(t_game *game)
{
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
	return (TRUE);
}

// Start the game->Parse the map->Validate the map
// Check map size->Set the player start->Count the collectibles
// Print the number of collectibles to catch->Initialize the game
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
	if (!init_game(game))
	{
		free_game(game);
		exit_error("Failed to initialize game");
	}
	return (TRUE);
}

// Main to start the game
// Initialize the game struct to 0
// Get the map path from the argument 1
int	main(int argc, char **argv)
{
	t_game	game;
	char	*ber;

	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
		exit_error("\nProgram usage: ./so_long <map.ber>");
	ber = ft_strrchr(argv[1], '.');
	if (!ber || ft_strcmp(ber, ".ber"))
		exit_error("Invalid map file, must be a .ber file");
	game.map_path = get_map_path(argv[1]);
	if (!start_game(&game, game.map_path))
		exit_error("Failed to start game");
	return (EXIT_SUCCESS);
}
