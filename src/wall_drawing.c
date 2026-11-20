/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:00:00 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/20 13:57:01 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	draw_no_texture_column(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		*(int *)(game->addr + (y * game->line_length
					+ x * (game->bits_per_pixel / 8))) = 0xFF0000;
		y++;
	}
}

void	draw_textured_column(t_game *game, t_ray *ray, int x, int *texture)
{
	float	fog_intensity;
	int		d;
	int		tex_y;
	int		color;
	int		y;

	fog_intensity = fmin(1.0, ray->perp_wall_dist / 5.0);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		d = y * 256 - WIN_H * 128 + ray->line_height * 128;
		tex_y = ((d * game->tex_h) / ray->line_height) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= game->tex_h)
			tex_y = game->tex_h - 1;
		color = texture[tex_y * game->tex_w + ray->tex_x];
		color = blend_colors(0x000000, color, fog_intensity);
		*(int *)(game->addr + (y * game->line_length
					+ x * (game->bits_per_pixel / 8))) = color;
		y++;
	}
}
