/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_texture_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:00:00 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/20 13:56:53 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	blend_colors(int color1, int color2, float opacity)
{
	int	r;
	int	g;
	int	b;

	r = (color1 >> 16) & 0xFF;
	g = (color1 >> 8) & 0xFF;
	b = color1 & 0xFF;
	if (g > 200 && r > 200 && b < 100)
		return (color1);
	r = (int)(r * opacity + ((color2 >> 16) & 0xFF) * (1 - opacity));
	g = (int)(g * opacity + ((color2 >> 8) & 0xFF) * (1 - opacity));
	b = (int)(b * opacity + (color2 & 0xFF) * (1 - opacity));
	return ((r << 16) | (g << 8) | b);
}

static int	*get_door_texture(t_game *game, t_ray *ray)
{
	int	door_state;

	if (!game->has_doors)
		return (game->buf_north);
	if (!game->buf_door)
		return (game->buf_north);
	door_state = game->door_states[ray->map_y][ray->map_x];
	if (door_state == 0)
		return (game->buf_door);
	else
		return (NULL);
}

static int	*get_directional_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (game->buf_east);
		else
			return (game->buf_west);
	}
	else
	{
		if (ray->dir_y > 0)
			return (game->buf_south);
		else
			return (game->buf_north);
	}
}

int	*get_wall_texture(t_game *game, t_ray *ray)
{
	char	map_char;
	int		*door_tex;

	if (ray->map_x < 0 || ray->map_x >= game->map_width
		|| ray->map_y < 0 || ray->map_y >= game->map_height)
		return (game->buf_north);
	map_char = game->map[ray->map_y][ray->map_x];
	if (map_char == 'D')
	{
		door_tex = get_door_texture(game, ray);
		if (door_tex)
			return (door_tex);
	}
	return (get_directional_texture(game, ray));
}
