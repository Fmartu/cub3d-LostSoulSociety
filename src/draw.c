/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:54:08 by fabi              #+#    #+#             */
/*   Updated: 2025/09/15 17:04:53 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	draw_line_step(int *coords, int *deltas, int *errors)
{
	int	e2;

	e2 = 2 * errors[2];
	if (e2 > -deltas[1])
	{
		errors[2] -= deltas[1];
		coords[0] += deltas[2];
	}
	if (e2 < deltas[0])
	{
		errors[2] += deltas[0];
		coords[1] += deltas[3];
	}
}

static void	init_line_params(int *coords, int *start)
{
	coords[0] = start[0];
	coords[1] = start[1];
}

static void	calc_line_deltas(int *deltas, int *start, int *end)
{
	deltas[0] = abs(end[0] - start[0]);
	deltas[1] = abs(end[1] - start[1]);
	if (start[0] < end[0])
		deltas[2] = 1;
	else
		deltas[2] = -1;
	if (start[1] < end[1])
		deltas[3] = 1;
	else
		deltas[3] = -1;
}

void	draw_line(t_game *game, int *start, int *end, int color)
{
	int	coords[2];
	int	deltas[4];
	int	errors[3];

	init_line_params(coords, start);
	calc_line_deltas(deltas, start, end);
	errors[2] = deltas[0] - deltas[1];
	while (coords[0] != end[0] || coords[1] != end[1])
	{
		if (coords[0] >= 0 && coords[0] < WIN_W
			&& coords[1] >= 0 && coords[1] < WIN_H)
			*(int *)(game->addr + (coords[1] * game->line_length
						+ coords[0] * (game->bits_per_pixel / 8))) = color;
		draw_line_step(coords, deltas, errors);
	}
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y < WIN_H / 2)
				*(int *)(game->addr + (y * game->line_length
							+ x * (game->bits_per_pixel / 8))) = 0xFFFFFF;
			else
				*(int *)(game->addr + (y * game->line_length
							+ x * (game->bits_per_pixel / 8))) = 0x000000;
			x++;
		}
		y++;
	}
}
