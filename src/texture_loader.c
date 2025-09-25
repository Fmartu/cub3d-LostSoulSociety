/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:07:44 by fabi              #+#    #+#             */
/*   Updated: 2025/09/18 22:17:31 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	load_texture_from_config(t_game *game,
		char *path, void **tex, int **buf)
{
	int	bpp;
	int	ll;
	int	endian;

	*tex = mlx_xpm_file_to_image(game->mlx, path, &game->tex_w, &game->tex_h);
	if (!*tex)
	{
		write(2, "Error: Cannot load texture: ", 29);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		return (0);
	}
	*buf = (int *)mlx_get_data_addr(*tex, &bpp, &ll, &endian);
	if (!*buf)
	{
		mlx_destroy_image(game->mlx, *tex);
		*tex = NULL;
		return (0);
	}
	return (1);
}

int	load_wall_textures_from_config(t_game *game)
{
	if (!game->tex_north_path || !game->tex_south_path
		|| !game->tex_east_path || !game->tex_west_path)
	{
		write(2, "Error: Missing texture paths in config\n", 40);
		return (0);
	}
	if (!load_texture_from_config(game, game->tex_north_path,
			&game->tex_north, &game->buf_north))
		return (0);
	if (!load_texture_from_config(game, game->tex_south_path,
			&game->tex_south, &game->buf_south))
		return (0);
	if (!load_texture_from_config(game, game->tex_east_path,
			&game->tex_east, &game->buf_east))
		return (0);
	if (!load_texture_from_config(game, game->tex_west_path,
			&game->tex_west, &game->buf_west))
		return (0);
	return (1);
}

void	load_textures(t_game *game)
{
	if (!load_wall_textures_from_config(game))
	{
		write(2, "Error: Failed to load wall textures from config\n", 48);
		exit(1);
	}
	if (!load_special_textures(game))
	{
		write(2, "Error: Failed to load special textures\n", 40);
		exit(1);
	}
	load_timer_textures(game);
}
