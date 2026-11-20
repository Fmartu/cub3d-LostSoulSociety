/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:00:00 by fmartusc            #+#    #+#           */
/*   Updated: 2025/09/18 23:26:54 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	validate_input(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		write(2, "Error: Invalid number of arguments\n", 36);
		write(2, "Usage: ./cub3D <map.cub>\n", 25);
		return (0);
	}
	if (!argv[1])
		return (0);
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
	{
		write(2, "Error: File must have .cub extension\n", 38);
		return (0);
	}
	return (1);
}

static int	init_mlx_system(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (write(2, "Error: Cannot initialize MLX\n", 30), 0);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "Cube3D");
	if (!game->win)
		return (write(2, "Error: Cannot create window\n", 29),
			free(game->mlx), 0);
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img)
	{
		write(2, "Error: Cannot create image\n", 28);
		mlx_destroy_window(game->mlx, game->win);
		free(game->mlx);
		return (0);
	}
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	return (1);
}

static void	setup_game_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 4, 1L << 2, mouse_event, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

static void	initialize_and_render(t_game *game, char *map_file)
{
	init_game(game, map_file);
	load_textures(game);
	verify_textures_loaded(game);
	init_audio(game);
	play_background_music(game);
	draw_background(game);
	raycast_scene(game);
	draw_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	draw_torch(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!validate_input(argc, argv))
		return (1);
	if (!init_mlx_system(&game))
		return (1);
	initialize_and_render(&game, argv[1]);
	setup_game_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
