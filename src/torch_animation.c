/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torch_animation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:04:16 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/15 14:13:15 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	update_torch_frame(t_game *game)
{
	time_t	current_time;

	current_time = time(NULL);
	if (difftime(current_time, game->last_frame_time) >= 0.04)
	{
		game->current_frame = (game->current_frame + 1)
			% game->torch_frame_count;
		game->last_frame_time = current_time;
	}
}

static int	should_draw_pixel(int color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (r > g + 20 && r > b + 20 && r > 30 && g < 100 && b < 100)
		return (0);
	return (1);
}

static void	draw_scaled_pixel(t_game *game, int color, int start_x,
		int start_y)
{
	if (start_y >= 0 && start_y < WIN_H && start_x >= 0 && start_x < WIN_W)
		*(int *)(game->addr + (start_y * game->line_length
					+ start_x * (game->bits_per_pixel / 8))) = color;
}

static void	draw_torch_row(t_game *game, int y, int start_x, int start_y)
{
	int	x;
	int	src_x;
	int	src_y;
	int	color;

	x = 0;
	while (x < (int)(game->torch_w * 3.0))
	{
		src_x = (int)(x / 3.0);
		src_y = (int)(y / 3.0);
		if (src_x >= game->torch_w)
			src_x = game->torch_w - 1;
		if (src_y >= game->torch_h)
			src_y = game->torch_h - 1;
		color = *(int *)((char *)game->torch_buffers[game->current_frame]
				+ src_y * game->torch_line_lengths[game->current_frame]
				+ src_x * (game->bits_per_pixel / 8));
		if (should_draw_pixel(color))
			draw_scaled_pixel(game, color, start_x + x, start_y + y);
		x++;
	}
}

void	draw_torch(t_game *game)
{
	int	scaled_height;
	int	start_x;
	int	start_y;
	int	y;

	if (!game->torch_buffers || game->torch_frame_count == 0)
		return ;
	scaled_height = (int)(game->torch_h * 3.0);
	update_torch_frame(game);
	if (!game->torch_buffers[game->current_frame])
		return ;
	start_x = 20;
	start_y = WIN_H - scaled_height;
	y = 0;
	while (y < scaled_height)
	{
		draw_torch_row(game, y, start_x, start_y);
		y++;
	}
}
