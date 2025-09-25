
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_interaction_fixed.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:38:25 by fabi              #+#    #+#             */
/*   Updated: 2025/01/18 10:00:00 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	initialize_door_states(t_game *game, int row)
{
	int	j;

	j = 0;
	while (j < game->map_width)
	{
		if (j < (int)ft_strlen(game->map[row]) && game->map[row][j] == 'D')
		{
			game->door_states[row][j] = 0;
			game->has_doors = 1;
		}
		else
			game->door_states[row][j] = 0;
		j++;
	}
}

static void	handle_start_screen_keys(t_game *game, int keycode)
{
	if (game->show_start > 0 && (keycode == 119 || keycode == 115
			|| keycode == 97 || keycode == 100))
	{
		if (game->show_start == 1 && !game->start_pressed)
		{
			game->show_start = 2;
			game->start_pressed = 1;
		}
		else if (game->show_start == 2 && game->start_pressed)
		{
			game->show_start = -1;
			play_background_music(game);
		}
	}
}

int	handle_esc_key(t_game *game)
{
	if (game->audio.background_music)
		Mix_HaltMusic();
	cleanup_audio(game);
	free_textures(game);
	free_map(game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		return (handle_esc_key(game));
	handle_start_screen_keys(game, keycode);
	if (game->show_start <= 0)
	{
		if (keycode == 119)
			game->keys.w = 1;
		else if (keycode == 115)
			game->keys.s = 1;
		else if (keycode == 97)
			game->keys.a = 1;
		else if (keycode == 100)
			game->keys.d = 1;
		else if (keycode == 65361)
			game->keys.left = 1;
		else if (keycode == 65363)
			game->keys.right = 1;
		else if (keycode == 32)
			handle_door_interaction(game);
	}
	return (0);
}

int	mouse_event(int button, int x, int y, t_game *game)
{
	double	old_dir_x;
	double	rot_speed;

	(void)x;
	(void)y;
	rot_speed = 0.1;
	if (button == 4)
	{
		old_dir_x = game->dir_x;
		game->dir_x = old_dir_x * cos(-rot_speed)
			- game->dir_y * sin(-rot_speed);
		game->dir_y = old_dir_x * sin(-rot_speed)
			+ game->dir_y * cos(-rot_speed);
	}
	if (button == 5)
	{
		old_dir_x = game->dir_x;
		game->dir_x = old_dir_x * cos(rot_speed)
			- game->dir_y * sin(rot_speed);
		game->dir_y = old_dir_x * sin(rot_speed)
			+ game->dir_y * cos(rot_speed);
	}
	return (0);
}
