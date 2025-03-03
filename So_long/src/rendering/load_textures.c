/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:32:50 by clu               #+#    #+#             */
/*   Updated: 2025/03/03 12:13:18 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Draw the map
	// Draw the floor, walls, and exit
	// Draw the collectibles to complete the map
void	draw_map(t_game *game, t_images *img)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			mlx_image_to_window(game->mlx, img->floor,
				x * TILE_SIZE, y * TILE_SIZE);
			if (game->map[y][x] == WALL)
				mlx_image_to_window(game->mlx, img->wall,
					x * TILE_SIZE, y * TILE_SIZE);
			if (game->map[y][x] == EXIT)
				mlx_image_to_window(game->mlx, img->exit,
					x * TILE_SIZE, y * TILE_SIZE);
			if (game->map[y][x] == COLLECT)
				mlx_image_to_window(game->mlx, img->collectible,
					x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

// Load the textures
	// Allocate memory for the textures
	// Load the textures from the png files
void	get_textures(t_game *game)
{
	game->tex = ft_calloc(1, sizeof(t_textures));
	if (!game->tex)
	{
		free_game(game);
		exit_error("Failed to allocate textures");
	}
	game->tex->floor = mlx_load_png("textures/floor.png");
	game->tex->wall = mlx_load_png("textures/wall.png");
	game->tex->collectible = mlx_load_png("textures/collectible.png");
	game->tex->player = mlx_load_png("textures/player.png");
	game->tex->exit = mlx_load_png("textures/exit.png");
	if (!game->tex->floor || !game->tex->wall || !game->tex->collectible
		|| !game->tex->player || !game->tex->exit)
	{
		free_game(game);
		exit_error("Failed to load one or more textures");
	}
}

// Load the images
	// Allocate memory for the images
	// Convert the textures to images
void	get_images(t_game *game)
{
	game->img = ft_calloc(1, sizeof(t_images));
	if (!game->img)
	{
		free_game(game);
		exit_error("Failed to allocate images");
	}
	game->img->floor = mlx_texture_to_image(game->mlx, game->tex->floor);
	game->img->wall = mlx_texture_to_image(game->mlx, game->tex->wall);
	game->img->collectible = mlx_texture_to_image(game->mlx,
			game->tex->collectible);
	game->img->player = mlx_texture_to_image(game->mlx, game->tex->player);
	game->img->exit = mlx_texture_to_image(game->mlx, game->tex->exit);
	if (!game->img->floor || !game->img->wall || !game->img->collectible
		|| !game->img->player || !game->img->exit)
	{
		free_game(game);
		exit_error("Failed to convert one or more textures to images");
	}
	mlx_delete_texture(game->tex->floor);
	mlx_delete_texture(game->tex->wall);
	mlx_delete_texture(game->tex->collectible);
	mlx_delete_texture(game->tex->player);
	mlx_delete_texture(game->tex->exit);
}
