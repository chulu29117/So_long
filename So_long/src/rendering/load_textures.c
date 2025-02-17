/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:32:50 by clu               #+#    #+#             */
/*   Updated: 2025/02/17 16:56:55 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_textures(t_game *game)
{
	// Allocate the textures structure
	game->tex = ft_calloc(1, sizeof(t_textures));
	if (!game->tex)
		exit_error("Failed to allocate textures");
	// Load textures from PNG files
	game->tex->floor = mlx_load_png("textures/floor.png");
	ft_printf("Loading floor\n");
	game->tex->wall = mlx_load_png("textures/wall.png");
	ft_printf("Loading wall\n");
	game->tex->collectible = mlx_load_png("textures/collectible.png");
	ft_printf("Loading collectible\n");
	game->tex->player = mlx_load_png("textures/player.png");
	ft_printf("Loading player\n");
	game->tex->exit = mlx_load_png("textures/exit.png");
	ft_printf("Loading exit\n");
	if (!game->tex->floor || !game->tex->wall || !game->tex->collectible ||
		!game->tex->player || !game->tex->exit)
		exit_error("Failed to load one or more textures");
}

void	get_images(t_game *game)
{
	// Allocate the images structure
	game->img = ft_calloc(1, sizeof(t_images));
	if (!game->img)
		exit_error("Failed to allocate images");
	// Convert textures to images and store them in the images structure
	game->img->floor = mlx_texture_to_image(game->mlx, game->tex->floor);
	ft_printf("Converting floor\n");
	game->img->wall = mlx_texture_to_image(game->mlx, game->tex->wall);
	ft_printf("Converting wall\n");
	game->img->collectible = mlx_texture_to_image(game->mlx, game->tex->collectible);
	ft_printf("Converting collectible\n");
	game->img->player = mlx_texture_to_image(game->mlx, game->tex->player);
	ft_printf("Converting player\n");
	game->img->exit = mlx_texture_to_image(game->mlx, game->tex->exit);
	ft_printf("Converting exit\n");
	// Check that all images converted successfully
	if (!game->img->floor || !game->img->wall || !game->img->collectible ||
		!game->img->player || !game->img->exit)
		exit_error("Failed to convert one or more textures to images");
	// Delete textures now that images have been created
	mlx_delete_texture(game->tex->floor);
	mlx_delete_texture(game->tex->wall);
	mlx_delete_texture(game->tex->collectible);
	// mlx_delete_texture(game->tex->player);
	mlx_delete_texture(game->tex->exit);
}

static void	draw_floor(t_game *game, t_images *img)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			mlx_image_to_window(game->mlx, img->floor, x * TILE_SIZE, y * TILE_SIZE);
			if (game->map[y][x] == WALL)
				mlx_image_to_window(game->mlx, img->wall, x * TILE_SIZE, y * TILE_SIZE);
			if (game->map[y][x] == EXIT)
				mlx_image_to_window(game->mlx, img->exit, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	draw_map(t_game *game, t_images *img)
{
	int	x;
	int	y;

	draw_floor(game, img);
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == COLLECT)
				mlx_image_to_window(game->mlx, img->collectible, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}
