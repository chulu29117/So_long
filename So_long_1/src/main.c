/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:39:27 by clu               #+#    #+#             */
/*   Updated: 2025/03/02 14:24:45 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Check if the file is a valid .ber file with valid filename.
int	is_valid_filename(const char *file)
{
	const char	*ext;

	ext = ".ber";
	if (!file || ft_strlen(file) <= ft_strlen(ext))
		return (FALSE);
	if (ft_strcmp(file + ft_strlen(file) - ft_strlen(ext), ext) != 0)
		return (FALSE);
	if (ft_strlen(file) == ft_strlen(ext))
		return (FALSE);
	if (file[ft_strlen(file) - ft_strlen(ext) - 1] == '/')
		return (FALSE);
	return (TRUE);
}

// Get the path of the map file
	// If the map file is in the maps directory, return the path
	// Otherwise, return the path with the maps directory prepended
static char	*get_map_path(char *arg)
{
	char	*path;

	if (!ft_strchr(arg, '/'))
	{
		path = ft_strjoin("maps/", arg);
		if (!path)
		{
			free(path);
			exit_error("Failed to allocate memory for map path");
		}
	}
	else
	{
		path = ft_strdup(arg);
		if (!path)
		{
			free(path);
			exit_error("Failed to allocate memory for map path");
		}
	}
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
	game->mlx = mlx_init(game->map_width, game->map_height, "so_long", false);
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
	count_collect(game);
	size_map(game, game->map);
	if (!set_player_start(game))
	{
		free(map_path);
		exit(EXIT_FAILURE);
	}
	if (!validate_map(game))
	{
		free(map_path);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	ft_printf("*** Number of Pikachus to catch: %d ***\n",
		game->total_collected);
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
	char	*map_path;

	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
		exit_error("Program usage: ./so_long <map.ber>");
	if (!is_valid_filename(argv[1]))
		exit_error("Invalid map, must have a valid name and .ber extension");
	map_path = get_map_path(argv[1]);
	if (!map_path)
	{
		free(map_path);
		exit_error("Failed to get map path");
	}
	if (!start_game(&game, map_path))
	{
		free(map_path);
		free_game(&game);
		exit_error("Failed to start game");
	}
	free(map_path);
	return (EXIT_SUCCESS);
}
