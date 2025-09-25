/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:45:33 by fabi              #+#    #+#             */
/*   Updated: 2025/09/15 14:49:50 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	init_ray_params(t_game *game, int x, t_ray *ray)
{
	ray->camera_x = 2 * x / (double)WIN_W - 1;
	ray->dir_x = game->dir_x - 0.66 * game->dir_y * ray->camera_x;
	ray->dir_y = game->dir_y + 0.66 * game->dir_x * ray->camera_x;
	ray->map_x = (int)game->pos_x;
	ray->map_y = (int)game->pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

void	free_torch_animation(t_game *game)
{
	int	i;

	if (game->torch_frames)
	{
		i = 0;
		while (i < game->torch_frame_count)
		{
			if (game->torch_frames[i])
				mlx_destroy_image(game->mlx, game->torch_frames[i]);
			i++;
		}
		free(game->torch_frames);
	}
	if (game->torch_buffers)
		free(game->torch_buffers);
}

int	load_start_texture(t_game *game)
{
	int	bpp;
	int	ll;
	int	endian;

	game->tex_start = mlx_xpm_file_to_image(game->mlx, "textures/start.xpm",
			&game->start_tex_w, &game->start_tex_h);
	if (!game->tex_start)
	{
		write(2, "Error: Failed to load start texture\n", 37);
		exit(1);
	}
	game->buf_start = (int *)mlx_get_data_addr(game->tex_start,
			&bpp, &ll, &endian);
	return (1);
}

void	cleanup_timer_textures(t_game *game, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (game->timer_textures[i])
			mlx_destroy_image(game->mlx, game->timer_textures[i]);
		i++;
	}
}
