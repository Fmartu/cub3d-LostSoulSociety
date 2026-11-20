/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:54:08 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/15 17:00:24 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	draw_map_cell(t_game *game, int *coords, int tile_size)
{
	int	map_x;
	int	map_y;

	map_x = coords[2] + (coords[1] * tile_size);
	map_y = coords[3] + (coords[0] * tile_size);
	if (game->map[coords[0]][coords[1]] == '1')
		draw_square(game, (int []){map_x, map_y}, tile_size, 0x404040);
	else if (game->map[coords[0]][coords[1]] == '0')
		draw_square(game, (int []){map_x, map_y}, tile_size, 0xC0C0C0);
	else if (game->map[coords[0]][coords[1]] == 'D')
	{
		if (game->door_states[coords[0]][coords[1]] == 0)
			draw_square(game, (int []){map_x, map_y}, tile_size, 0xFFFF00);
		else
			draw_square(game, (int []){map_x, map_y}, tile_size, 0x8B0000);
	}
}

static void	draw_map_tile(t_game *game, int tile_size, int offset_x,
		int offset_y)
{
	int	coords[4];

	coords[0] = 0;
	while (coords[0] < game->map_height)
	{
		coords[1] = 0;
		coords[2] = offset_x;
		coords[3] = offset_y;
		while (coords[1] < game->map_width)
		{
			draw_map_cell(game, coords, tile_size);
			coords[1]++;
		}
		coords[0]++;
	}
}

static void	calculate_map_params(t_game *game, int *tile_size,
		int *offset_x, int *offset_y)
{
	if (game->map_width > game->map_height)
		*tile_size = 200 / game->map_width;
	else
		*tile_size = 200 / game->map_height;
	if (*tile_size < 4)
		*tile_size = 4;
	*offset_x = WIN_W - (game->map_width * *tile_size) - 20;
	*offset_y = WIN_H - (game->map_height * *tile_size) - 20;
	if (*offset_x < 20)
		*offset_x = 20;
	if (*offset_y < 20)
		*offset_y = 20;
}

static void	draw_player_on_map(t_game *game, int tile_size,
		int offset_x, int offset_y)
{
	int	player_pos[2];
	int	square_pos[2];
	int	line_end[2];

	player_pos[0] = offset_x + (int)(game->pos_x * tile_size);
	player_pos[1] = offset_y + (int)(game->pos_y * tile_size);
	square_pos[0] = player_pos[0] - tile_size / 4;
	square_pos[1] = player_pos[1] - tile_size / 4;
	draw_square(game, square_pos, tile_size / 2, 0xFF0000);
	line_end[0] = player_pos[0] + (int)(game->dir_x * tile_size * 0.8);
	line_end[1] = player_pos[1] + (int)(game->dir_y * tile_size * 0.8);
	draw_line(game, player_pos, line_end, 0x00FF00);
}

void	draw_map(t_game *game)
{
	int	tile_size;
	int	offset_x;
	int	offset_y;

	calculate_map_params(game, &tile_size, &offset_x, &offset_y);
	draw_map_tile(game, tile_size, offset_x, offset_y);
	draw_player_on_map(game, tile_size, offset_x, offset_y);
}
