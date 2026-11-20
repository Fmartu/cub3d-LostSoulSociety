/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:56:34 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/15 14:15:43 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	load_end_texture(t_game *game)
{
	int	bpp;
	int	ll;
	int	endian;

	game->tex_end = mlx_xpm_file_to_image(game->mlx, "textures/end.xpm",
			&game->end_tex_w, &game->end_tex_h);
	if (!game->tex_end)
	{
		write(2, "Error: Cannot load end.xpm texture\n", 36);
		return ;
	}
	game->buf_end = (int *)mlx_get_data_addr(game->tex_end, &bpp, &ll, &endian);
	if (!game->buf_end)
	{
		write(2, "Error: Cannot get end texture buffer\n", 38);
		mlx_destroy_image(game->mlx, game->tex_end);
		game->tex_end = NULL;
		return ;
	}
}

static void	draw_end_pixel(t_game *game, int *buf, int x, int y)
{
	double	scale_x;
	double	scale_y;
	int		tex_x;
	int		tex_y;

	scale_x = (double)game->end_tex_w / WIN_W;
	scale_y = (double)game->end_tex_h / WIN_H;
	tex_x = (int)(x * scale_x);
	tex_y = (int)(y * scale_y);
	if (tex_x >= game->end_tex_w)
		tex_x = game->end_tex_w - 1;
	if (tex_y >= game->end_tex_h)
		tex_y = game->end_tex_h - 1;
	*(int *)(game->addr + (y * game->line_length
				+ x * (game->bits_per_pixel / 8)))
		= buf[tex_y * game->end_tex_w + tex_x];
}

static void	draw_end_background(t_game *game)
{
	int		x;
	int		y;
	int		*buf;

	if (!game->buf_end || game->end_tex_w == 0 || game->end_tex_h == 0)
		return ;
	buf = game->buf_end;
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			draw_end_pixel(game, buf, x, y);
			x++;
		}
		y++;
	}
}

static void	draw_victory_message(t_game *game)
{
	static int	message_shown = 0;
	int			total_doors;

	total_doors = count_open_doors(game);
	if (total_doors > 0 && game->timer_stopped && !message_shown)
		message_shown = 1;
}

void	draw_end_screen(t_game *game)
{
	draw_end_background(game);
	draw_timer(game);
	draw_victory_message(game);
}
