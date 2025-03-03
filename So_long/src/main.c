/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:39:27 by clu               #+#    #+#             */
/*   Updated: 2025/03/03 14:36:40 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_filename(char *file);
static int	init_game(t_game *game);
static int	start_game(t_game *game, char *map_path);

// Main to start the game
	// Initialize the game struct to 0
	// Get the map path from the argument 1
int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
		exit_error("Program usage: ./so_long <map.ber>");
	if (!is_valid_filename(argv[1]))
	{
		if (access(argv[1], F_OK) == -1)
		{
			ft_putstr_fd("Error\nNonexistent map file: ", STDERR_FILENO);
			ft_putendl_fd(argv[1], STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		exit_error("Invalid map: must have a valid name and .ber extension");
	}
	if (!start_game(&game, argv[1]))
	{
		free_game(&game);
		exit_error("Failed to start game");
	}
	return (EXIT_SUCCESS);
}

// Check if the file is a valid .ber file with valid filename.
static int	is_valid_filename(char *map_file)
{
	const char	*ext;
	size_t		file_len;
	size_t		ext_len;

	ext = ".ber";
	file_len = ft_strlen(map_file);
	ext_len = ft_strlen(ext);
	if (!map_file || file_len <= ext_len)
		return (FALSE);
	if (ft_strcmp(map_file + file_len - ext_len, ext) != 0)
		return (FALSE);
	return (TRUE);
}

// Start the game->Parse the map->Validate the map
	// Check map size->Set the player start->Count the collectibles
	// Print the number of collectibles to catch->Initialize the game
static int	start_game(t_game *game, char *map_file)
{
	parse_map(map_file, game);
	count_collect(game);
	size_map(game, game->map);
	if (!set_player_start(game))
	{
		free_game(game);
		exit(EXIT_FAILURE);
	}
	if (!validate_map(game))
	{
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
