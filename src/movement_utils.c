/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:44:28 by fabi              #+#    #+#             */
/*   Updated: 2025/09/15 12:44:36 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	can_move_to(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_x < 0 || map_x >= game->map_width
		|| map_y < 0 || map_y >= game->map_height)
		return (0);
	if (game->map[map_y][map_x] == '1' || game->map[map_y][map_x] == ' ')
		return (0);
	if (game->map[map_y][map_x] == 'D' && game->door_states[map_y][map_x] == 0)
		return (0);
	return (1);
}

void	move_forward_backward(t_game *game, int forward)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.1;
	if (forward)
	{
		new_x = game->pos_x + game->dir_x * move_speed;
		new_y = game->pos_y + game->dir_y * move_speed;
	}
	else
	{
		new_x = game->pos_x - game->dir_x * move_speed;
		new_y = game->pos_y - game->dir_y * move_speed;
	}
	if (can_move_to(game, new_x, game->pos_y))
		game->pos_x = new_x;
	if (can_move_to(game, game->pos_x, new_y))
		game->pos_y = new_y;
}
