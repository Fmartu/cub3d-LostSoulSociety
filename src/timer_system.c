/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:03:07 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/15 17:29:31 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	draw_timer_digits(t_game *game, int minutes, int seconds,
		t_off2 start_pos)
{
	int		char_width;
	int		char_spacing;
	float	scale;
	t_off2	offset;

	char_width = game->timer_tex_w;
	char_spacing = 1;
	scale = 0.3;
	offset.x = start_pos.x;
	offset.y = start_pos.y;
	draw_timer_char(game, game->timer_textures[minutes / 10], offset);
	offset.x = start_pos.x + (int)(char_width * scale);
	draw_timer_char(game, game->timer_textures[minutes % 10], offset);
	offset.x = start_pos.x + (int)(char_width * 2 * scale) + char_spacing;
	draw_timer_char(game, game->timer_textures[10], offset);
	offset.x = start_pos.x + (int)(char_width * 3 * scale) + char_spacing;
	draw_timer_char(game, game->timer_textures[seconds / 10], offset);
	offset.x = start_pos.x + (int)(char_width * 4 * scale) + char_spacing;
	draw_timer_char(game, game->timer_textures[seconds % 10], offset);
}

static t_off2	calculate_timer_position(t_game *game, int total_width,
		int total_height)
{
	t_off2	pos;

	if (game->show_end)
	{
		pos.x = (WIN_W / 2) - total_width - 30;
		pos.y = (WIN_H * 1 / 3);
	}
	else
	{
		pos.x = (WIN_W - total_width) / 2;
		pos.y = WIN_H - total_height - 10;
	}
	return (pos);
}

void	draw_timer(t_game *game)
{
	time_t	current_time;
	double	elapsed_time;
	t_off2	dimensions;
	t_off2	time_vals;
	t_off2	start_pos;

	if (!game->timer_textures[0] || game->timer_tex_w == 0
		|| game->timer_tex_h == 0)
		return ;
	if (game->timer_stopped)
		current_time = game->end_time;
	else
		current_time = time(NULL);
	elapsed_time = difftime(current_time, game->start_time);
	time_vals.x = (int)(elapsed_time / 60);
	time_vals.y = (int)(elapsed_time - time_vals.x * 60);
	dimensions.x = (int)((game->timer_tex_w * 5 + 2) * 0.3);
	dimensions.y = (int)(game->timer_tex_h * 0.3);
	start_pos = calculate_timer_position(game, dimensions.x, dimensions.y);
	draw_timer_digits(game, time_vals.x, time_vals.y, start_pos);
}

void	draw_door_counter(t_game *game)
{
	int	open_doors;
	int	total_doors;

	open_doors = count_open_doors(game);
	total_doors = count_total_doors(game);
	if (open_doors == total_doors && total_doors > 0)
	{
		if (!game->timer_stopped)
		{
			game->end_time = time(NULL);
			game->timer_stopped = 1;
			play_end_music(game);
		}
		game->show_end = 1;
	}
}
