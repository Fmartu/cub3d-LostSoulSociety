/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:00:00 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/18 23:07:49 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	draw_ceiling_column(t_game *game, int x, int draw_start)
{
	int		y;
	float	sky_fog_intensity;
	int		final_color;

	y = 0;
	while (y < draw_start)
	{
		sky_fog_intensity = fmin(1.0, (float)y / (WIN_H / 4));
		final_color = blend_colors(0xFFFFFF, 0x000000, sky_fog_intensity);
		*(int *)(game->addr + (y * game->line_length
					+ x * (game->bits_per_pixel / 8))) = final_color;
		y++;
	}
}

static void	draw_floor_column(t_game *game, int x, int draw_end)
{
	int		y;
	float	floor_fog_intensity;
	int		final_floor_color;

	y = draw_end;
	while (y < WIN_H)
	{
		floor_fog_intensity = fmin(1.0, (float)(y - WIN_H / 2) / (WIN_H / 2));
		final_floor_color = blend_colors(0x000000, 0x000000,
				floor_fog_intensity);
		*(int *)(game->addr + (y * game->line_length
					+ x * (game->bits_per_pixel / 8))) = final_floor_color;
		y++;
	}
}

void	draw_wall_column(t_game *game, t_ray *ray, int x, int y)
{
	int	*texture;

	(void)y;
	draw_ceiling_column(game, x, ray->draw_start);
	texture = get_wall_texture(game, ray);
	if (!texture)
		draw_no_texture_column(game, ray, x);
	else
		draw_textured_column(game, ray, x, texture);
	draw_floor_column(game, x, ray->draw_end);
}
