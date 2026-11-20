/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:00:00 by fmartusc            #+#    #+#           */
/*   Updated: 2025/09/18 23:34:54 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	set_player_direction(t_game *game, char direction)
{
	if (direction == 'N')
	{
		game->dir_x = 0.0001;
		game->dir_y = -1.0;
	}
	else if (direction == 'S')
	{
		game->dir_x = -0.0001;
		game->dir_y = 1.0;
	}
	else if (direction == 'E')
	{
		game->dir_x = 1.0;
		game->dir_y = 0.0001;
	}
	else if (direction == 'W')
	{
		game->dir_x = -1.0;
		game->dir_y = -0.0001;
	}
}

void	set_player_position(t_game *game, int i)
{
	int		j;
	double	old_dir_x;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < (int)ft_strlen(game->map[i]))
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
				game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->pos_x = j + 0.5;
				game->pos_y = i + 0.5;
				set_player_direction(game, game->map[i][j]);
				old_dir_x = game->dir_x;
				game->dir_x = old_dir_x * cos(0.1) - game->dir_y * sin(0.1);
				game->dir_y = old_dir_x * sin(0.1) + game->dir_y * cos(0.1);
				game->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

static void	init_game_values(t_game *game)
{
	int	i;

	game->keys.w = 0;
	game->keys.s = 0;
	game->keys.a = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->start_time = time(NULL);
	game->end_time = 0;
	game->timer_stopped = 0;
	game->black_screen_start = time(NULL);
	game->show_start = 0;
	game->show_end = 0;
	game->has_doors = 0;
	i = 0;
	while (i < 11)
	{
		game->timer_textures[i] = NULL;
		i++;
	}
	game->timer_tex_w = 0;
	game->timer_tex_h = 0;
}

static void	cleanup_on_error(t_game *game)
{
	free_map(game);
	if (game->tex_north_path)
		free(game->tex_north_path);
	if (game->tex_south_path)
		free(game->tex_south_path);
	if (game->tex_east_path)
		free(game->tex_east_path);
	if (game->tex_west_path)
		free(game->tex_west_path);
	if (game->floor_color)
		free(game->floor_color);
	if (game->ceiling_color)
		free(game->ceiling_color);
}

void	init_game(t_game *game, const char *map_file)
{
	parse_map(game, map_file);
	calculate_map_dimensions(game);
	if (!validate_map(game))
	{
		cleanup_on_error(game);
		exit(1);
	}
	set_player_position(game, 0);
	init_game_values(game);
	initialize_all_doors(game);
	load_torch_animation(game);
	load_start_textures(game);
}
