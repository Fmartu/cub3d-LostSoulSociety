/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:00:00 by fabi                #+#    #+#           */
/*   Updated: 2025/09/15 15:05:04 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	render_black_screen(t_game *game)
{
	int		x;
	int		y;
	time_t	current_time;
	double	elapsed_time;

	current_time = time(NULL);
	elapsed_time = difftime(current_time, game->black_screen_start);
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			*(int *)(game->addr + (y * game->line_length
						+ x * (game->bits_per_pixel / 8))) = 0x000000;
			x++;
		}
		y++;
	}
	if (elapsed_time < 0.1)
		play_door_sound(game);
	if (elapsed_time >= 7.0)
		game->show_start = 1;
}

static void	render_start_screen(t_game *game)
{
	draw_start_screen(game);
}

static void	render_end_screen(t_game *game)
{
	draw_end_screen(game);
}

static void	render_game_screen(t_game *game)
{
	move_player(game);
	draw_background(game);
	raycast_scene(game);
	draw_map(game);
	draw_timer(game);
	draw_door_counter(game);
	draw_torch(game);
}

int	game_loop(t_game *game)
{
	if (game->show_start == 0)
		render_black_screen(game);
	else if (game->show_start > 0)
		render_start_screen(game);
	else if (game->show_end)
		render_end_screen(game);
	else
		render_game_screen(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
