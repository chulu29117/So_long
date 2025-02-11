/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:19:51 by clu               #+#    #+#             */
/*   Updated: 2025/02/11 23:27:14 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <memory.h>
# include <time.h>

# define PIXELS 64

// typedef struct s_img
// {
// 	mlx_image_t	*tree;
// 	mlx_image_t	*floor;
// 	mlx_image_t	*eyeball;
// 	mlx_image_t	*player;
// 	mlx_image_t	*gravestone;
// 	mlx_image_t	*moves_print;
// 	mlx_image_t	*moves_nbr;
// 	mlx_image_t	*eyeball_nbr;
// 	mlx_image_t	*enemy[3];
// 	int			enemy_frame;

// }	t_img;

// typedef struct s_game
// {
// 	t_img			*img;
// 	mlx_t			*mlx;
// 	char			**grid;
// 	size_t			width;
// 	size_t			height;
// 	size_t			eyeball;
// 	size_t			steps;
// 	size_t			collected;
// 	size_t			player_x;
// 	size_t			player_y;
// 	size_t			exit_x;
// 	size_t			exit_y;
// 	mlx_texture_t	*player_up;
// 	mlx_texture_t	*player_down;
// 	mlx_texture_t	*player_left;
// 	mlx_texture_t	*player_right;

// 	double			time;
// 	int				enemy_frames;
// }	t_game;

// //map validation check1
// void	check_empty_line(char *map);
// void	check_invalid_content(int i);
// void	check_map_content(char *map);
// void	check_map_size(char **grid);

// //map validation check2
// void	check_map_shape(char *map);
// void	check_wall(t_game *game);

// //path check
// int		flood_fill(t_game *game);
// int		check_path(t_game *temp, size_t x, size_t y);
// void	free_grid(char **grid, size_t height);

// //mixed
// void	check_game_status(t_game *game);
// void	check_status(t_game *game);
// void	delay(int milliseconds);
// size_t	row_count(char **map);

// //parse map
// void	check_file_extension(char *file);
// char	*read_map(char *map);
// int		count_eyeball(t_game *game);
// size_t	get_player_pos(t_game *game, char c);
// size_t	get_exit_pos(t_game *game, char c);

// //render map
// void	fill_background(t_game *data);
// void	render_map(t_game *data);
// void	image_select(t_game *data, size_t y, size_t x);

// //init
// t_game	*initialize_game_struct(char **grid);
// t_game	*initialize_data(char *str);
// t_img	*initialize_img_struct(mlx_t *mlx, t_game *game);
// t_img	*load_tree_texture(mlx_t *mlx, t_img *img, t_game *game);
// t_img	*load_gravestone_texture(mlx_t *mlx, t_img *img, t_game *game);
// t_img	*load_eyeball_texture(mlx_t *mlx, t_img *img, t_game *game);
// t_img	*load_player_texture(mlx_t *mlx, t_img *img, t_game *game);
// t_img	*load_floor_texture(mlx_t *mlx, t_img *img, t_game *game);

// //move
// void	load_other_player_textures(t_game *game);
// void	move_select(t_game *game, char line, char direction);
// void	load_player(t_game *game, char direction);
// void	move_player(t_game *game, char line, char direction);
// void	move_hook(mlx_key_data_t keydata, void *data);

// //move direction
// void	remove_eyeball(t_game *game, int x, int y);
// t_game	*move_up(t_game *game);
// t_game	*move_down(t_game *game);
// t_game	*move_left(t_game *game);
// t_game	*move_right(t_game *game);

// //screen string
// void	string_to_screen(t_game *game);
// void	print_eyeball(t_game *game);
// void	print_moves( t_game *game);

// //error and delete
// void	delete_map(char **grid, int32_t height);
// void	error_message(char *str, t_game *game);
// void	free_direction_texture(t_game *game);

#endif
