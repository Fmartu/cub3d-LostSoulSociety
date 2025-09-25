/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:00:00 by fabi              #+#    #+#             */
/*   Updated: 2025/09/18 23:11:08 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	try_load_door_image(t_game *game)
{
	game->tex_door = mlx_xpm_file_to_image(game->mlx, "./textures/door.xpm",
			&game->tex_w, &game->tex_h);
	if (!game->tex_door)
	{
		game->tex_door = mlx_xpm_file_to_image(game->mlx, "textures/door.xpm",
				&game->tex_w, &game->tex_h);
		if (!game->tex_door)
		{
			write(2, "Error: Cannot load door texture\n", 33);
			return (0);
		}
	}
	return (1);
}

static int	load_door_texture(t_game *game)
{
	int	bpp;
	int	ll;
	int	endian;

	if (!try_load_door_image(game))
		return (0);
	game->buf_door = (int *)mlx_get_data_addr(game->tex_door, &bpp, &ll,
			&endian);
	if (!game->buf_door)
	{
		mlx_destroy_image(game->mlx, game->tex_door);
		game->tex_door = NULL;
		return (0);
	}
	return (1);
}

static int	load_end_sticker_textures(t_game *game)
{
	int	bpp;
	int	ll;
	int	endian;

	game->tex_end = mlx_xpm_file_to_image(game->mlx, "./textures/end.xpm",
			&game->end_tex_w, &game->end_tex_h);
	if (!game->tex_end)
		return (0);
	game->buf_end = (int *)mlx_get_data_addr(game->tex_end, &bpp, &ll, &endian);
	if (!game->buf_end)
		return (0);
	game->tex_sticker = mlx_xpm_file_to_image(game->mlx,
			"./textures/sticker.xpm", &game->sticker_tex_w,
			&game->sticker_tex_h);
	if (!game->tex_sticker)
		return (0);
	game->buf_sticker = (int *)mlx_get_data_addr(game->tex_sticker,
			&bpp, &ll, &endian);
	return (game->buf_sticker != NULL);
}

int	load_special_textures(t_game *game)
{
	if (game->has_doors)
	{
		if (!load_door_texture(game))
			return (0);
	}
	else
	{
		game->tex_door = NULL;
		game->buf_door = NULL;
	}
	if (!load_end_sticker_textures(game))
		return (0);
	return (1);
}
