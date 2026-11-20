/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:08:17 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/15 14:09:03 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	load_start2_texture(t_game *game)
{
	int	bpp;
	int	ll;
	int	endian;

	game->tex_start2 = mlx_xpm_file_to_image(game->mlx,
			"textures/start2.xpm", &game->start_tex_w, &game->start_tex_h);
	if (!game->tex_start2)
	{
		write(2, "Error: Failed to load start2 texture\n", 38);
		exit(1);
	}
	game->buf_start2 = (int *)mlx_get_data_addr(game->tex_start2,
			&bpp, &ll, &endian);
	return (1);
}

void	load_start_textures(t_game *game)
{
	load_start_texture(game);
	load_start2_texture(game);
	game->show_start = 1;
	game->start_pressed = 0;
}

static void	draw_start_screen_pixel(t_game *game, int *buf, int x, int y)
{
	double	scale_x;
	double	scale_y;
	int		tex_x;
	int		tex_y;

	scale_x = (double)game->start_tex_w / WIN_W;
	scale_y = (double)game->start_tex_h / WIN_H;
	tex_x = (int)(x * scale_x);
	tex_y = (int)(y * scale_y);
	if (tex_x >= game->start_tex_w)
		tex_x = game->start_tex_w - 1;
	if (tex_y >= game->start_tex_h)
		tex_y = game->start_tex_h - 1;
	*(int *)(game->addr + (y * game->line_length
				+ x * (game->bits_per_pixel / 8)))
		= buf[tex_y * game->start_tex_w + tex_x];
}

static int	*get_start_buffer(t_game *game)
{
	if (game->show_start == 1)
		return (game->buf_start);
	else
		return (game->buf_start2);
}

void	draw_start_screen(t_game *game)
{
	int		x;
	int		y;
	int		*buf;

	if (!game->buf_start || !game->buf_start2
		|| game->start_tex_w == 0 || game->start_tex_h == 0)
		return ;
	buf = get_start_buffer(game);
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			draw_start_screen_pixel(game, buf, x, y);
			x++;
		}
		y++;
	}
}
