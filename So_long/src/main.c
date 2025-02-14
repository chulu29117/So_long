/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:39:27 by clu               #+#    #+#             */
/*   Updated: 2025/02/14 21:14:18 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	key_handler(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map.ber>\n", argv[0]);
		return (EXIT_FAILURE);	
	}
	/*Parsing the map file*/
	parse_map(argv[1], &game);
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
	mlx_key_data(game.mlx, key_handler, &game);
	/*Start the MLX42 event loop*/
	mlx_loop(game.mlx);
	/*Clean up after loop ends*/
	mlx_terminate(game.mlx);
	free_map(&game.map);
	return (EXIT_SUCCESS);
}
