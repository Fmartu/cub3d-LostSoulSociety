/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:38:25 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/15 13:35:39 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	close_window(t_game *game)
{
	free_game(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 119)
		game->keys.w = 0;
	else if (keycode == 115)
		game->keys.s = 0;
	else if (keycode == 97)
		game->keys.a = 0;
	else if (keycode == 100)
		game->keys.d = 0;
	else if (keycode == 65361)
		game->keys.left = 0;
	else if (keycode == 65363)
		game->keys.right = 0;
	return (0);
}

static void	check_door_distance_and_toggle(t_game *game, int check_x,
		int check_y)
{
	double	dx;
	double	dy;
	double	dist;

	dx = check_x - game->pos_x;
	dy = check_y - game->pos_y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist < 2.0)
	{
		game->door_states[check_y][check_x]
			= !game->door_states[check_y][check_x];
		if (game->door_states[check_y][check_x] == 1)
			play_door_sound(game);
	}
}

void	handle_door_interaction(t_game *game)
{
	int		check_x;
	int		check_y;
	double	check_dist;
	double	normalized_dir_x;
	double	normalized_dir_y;

	check_dist = sqrt(game->dir_x * game->dir_x + game->dir_y * game->dir_y);
	normalized_dir_x = game->dir_x / check_dist;
	normalized_dir_y = game->dir_y / check_dist;
	check_x = (int)(game->pos_x + normalized_dir_x * 1.5);
	check_y = (int)(game->pos_y + normalized_dir_y * 1.5);
	if (check_x < 0 || check_x >= game->map_width
		|| check_y < 0 || check_y >= game->map_height)
		return ;
	if (game->map[check_y][check_x] == 'D')
		check_door_distance_and_toggle(game, check_x, check_y);
}
