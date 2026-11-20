/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:19:42 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/15 17:30:11 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	count_open_doors(t_game *game)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'D' && game->door_states[i][j] == 1)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	count_total_doors(t_game *game)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'D')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static void	draw_timer_pixel(t_game *game, t_timer_px p)
{
	int	dst_x;
	int	dst_y;
	int	byte_off;

	dst_x = p.x_offset + p.scaled_x;
	dst_y = p.y_offset + p.scaled_y;
	if (dst_y >= 0 && dst_y < WIN_H && dst_x >= 0 && dst_x < WIN_W)
	{
		byte_off = (dst_y * game->line_length)
			+ (dst_x * (game->bits_per_pixel / 8));
		*(int *)(game->addr + byte_off) = p.color;
	}
}

static void	draw_timer_char_row(t_game *game, int *buffer, int y,
		t_off2 off)
{
	int			x;
	int			color;
	float		scale;
	t_timer_px	p;

	scale = 0.3f;
	x = 0;
	while (x < game->timer_tex_w)
	{
		color = *(int *)((char *)buffer
				+ y * (game->timer_tex_w * (game->bits_per_pixel / 8))
				+ x * (game->bits_per_pixel / 8));
		if (color != 0x000000)
		{
			p.color = color;
			p.x_offset = off.x;
			p.y_offset = off.y;
			p.scaled_x = (int)(x * scale);
			p.scaled_y = (int)(y * scale);
			draw_timer_pixel(game, p);
		}
		x++;
	}
}

void	draw_timer_char(t_game *game, void *texture_ptr, t_off2 offset)
{
	int		*buffer;
	int		bpp;
	int		ll;
	int		endian;
	int		y;

	if (!texture_ptr || game->timer_tex_w == 0 || game->timer_tex_h == 0)
		return ;
	buffer = (int *)mlx_get_data_addr(texture_ptr, &bpp, &ll, &endian);
	(void)bpp;
	(void)ll;
	(void)endian;
	y = 0;
	while (y < game->timer_tex_h)
	{
		draw_timer_char_row(game, buffer, y, offset);
		y++;
	}
}
