/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:39:27 by clu               #+#    #+#             */
/*   Updated: 2025/02/14 22:30:06 by clu              ###   ########.fr       */
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
	if (!validate_map(&game.map))
	{
		ft_printf("Error\nInvalid map\n");
		free_map(&game.map);
		return (EXIT_FAILURE);
	}
	/*Initialize MLX42 and make game window*/
	game.mlx = mlx_init(800, 600, "so_long", true);
	if (!game.mlx)
	{
		free_map(&game.map);
		return (EXIT_FAILURE);
	}
	/*Load textures for walls, collectibles, exit, floor, and player*/
	load_textures(&game);
	/*Render the initial map*/
	render_map(&game);
	/*Set up key event handling*/
	mlx_loop_hook(game.mlx, hook, &game);
	/*Start the MLX42 event loop*/
	mlx_loop(game.mlx);
	/*Clean up after loop ends*/
	mlx_terminate(game.mlx);
	free_map(&game.map);
	return (EXIT_SUCCESS);
}
