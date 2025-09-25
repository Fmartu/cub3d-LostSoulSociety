/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:13:45 by fabi              #+#    #+#             */
/*   Updated: 2025/09/15 12:44:10 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	move_left_right(t_game *game, int left)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.1;
	if (left)
	{
		new_x = game->pos_x + game->dir_y * move_speed;
		new_y = game->pos_y - game->dir_x * move_speed;
	}
	else
	{
		new_x = game->pos_x - game->dir_y * move_speed;
		new_y = game->pos_y + game->dir_x * move_speed;
	}
	if (can_move_to(game, new_x, game->pos_y))
		game->pos_x = new_x;
	if (can_move_to(game, game->pos_x, new_y))
		game->pos_y = new_y;
}

static void	rotate_player(t_game *game, int left)
{
	double	old_dir_x;
	double	rot_speed;

	rot_speed = 0.05;
	old_dir_x = game->dir_x;
	if (left)
	{
		game->dir_x = old_dir_x * cos(-rot_speed)
			- game->dir_y * sin(-rot_speed);
		game->dir_y = old_dir_x * sin(-rot_speed)
			+ game->dir_y * cos(-rot_speed);
	}
	else
	{
		game->dir_x = old_dir_x * cos(rot_speed)
			- game->dir_y * sin(rot_speed);
		game->dir_y = old_dir_x * sin(rot_speed)
			+ game->dir_y * cos(rot_speed);
	}
}

static void	handle_movement_keys(t_game *game)
{
	if (game->keys.w == 1)
	{
		move_forward_backward(game, 1);
		game->keys.w = 0;
	}
	if (game->keys.s == 1)
	{
		move_forward_backward(game, 0);
		game->keys.s = 0;
	}
	if (game->keys.a == 1)
	{
		move_left_right(game, 1);
		game->keys.a = 0;
	}
	if (game->keys.d == 1)
	{
		move_left_right(game, 0);
		game->keys.d = 0;
	}
}

static void	handle_rotation_keys(t_game *game)
{
	if (game->keys.left == 1)
	{
		rotate_player(game, 1);
		game->keys.left = 0;
	}
	if (game->keys.right == 1)
	{
		rotate_player(game, 0);
		game->keys.right = 0;
	}
}

void	move_player(t_game *game)
{
	handle_movement_keys(game);
	handle_rotation_keys(game);
}
