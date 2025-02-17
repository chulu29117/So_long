/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:39:27 by clu               #+#    #+#             */
/*   Updated: 2025/02/17 14:02:31 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*get_map_path(char *arg)
{
	char	*path;

	/* If there's no '/' in the argument, assume it's in the maps/ directory */
	if (!ft_strchr(arg, '/'))
		path = ft_strjoin("maps/", arg);
	else
		path = ft_strdup(arg);
	return (path);
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
	/*Parsing the map file*/
	parse_map(map_path, &game);
	free(map_path);
	/*Validate the map (checking dimensions, elements)*/
	if (!validate_map(&game))
	{
		ft_printf("Error\nInvalid map\n");
		free_map(game.map);
		return (EXIT_FAILURE);
	}
	set_player_start(&game);
	/*Initialize MLX42 and make game window*/
	game.mlx = mlx_init(WIDTH, HEIGHT, "so_long", true);
	if (!game.mlx)
	{
		free_map(game.map);
		return (EXIT_FAILURE);
	}
	/*Load textures for walls, collectibles, exit, floor, and player*/
	get_textures(&game);
	get_images(&game);
	draw_map(&game, game.img);
	/*Render the initial map*/
	render_map(&game);
	/*Set up key event handling*/
	mlx_key_hook(game.mlx, keyhook, &game);
	/*Start the MLX42 event loop*/
	mlx_loop(game.mlx);
	/*Clean up after loop ends*/	
	mlx_terminate(game.mlx);
	free_map(game.map);
	free(game.img);
	free(game.tex);
	return (EXIT_SUCCESS);
}
