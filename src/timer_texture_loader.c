/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_texture_loader.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:00:00 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/20 14:00:50 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	create_timer_path(char *path, int i)
{
	if (i < 10)
		snprintf(path, 256, "textures/numbers/%d.xpm", i);
	else
		snprintf(path, 256, "textures/numbers/divider.xpm");
}

static void	load_single_timer_texture(t_game *game, int i, char *path)
{
	int	bpp;
	int	ll;
	int	endian;

	game->timer_textures[i] = mlx_xpm_file_to_image(game->mlx, path,
			&game->timer_tex_w, &game->timer_tex_h);
	if (!game->timer_textures[i])
	{
		write(2, "Error: Cannot load timer texture: ", 35);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		cleanup_timer_textures(game, i);
		exit(1);
	}
	mlx_get_data_addr(game->timer_textures[i], &bpp, &ll, &endian);
}

void	load_timer_textures(t_game *game)
{
	char	path[256];
	int		i;

	i = 0;
	while (i < 11)
	{
		create_timer_path(path, i);
		load_single_timer_texture(game, i, path);
		i++;
	}
}
