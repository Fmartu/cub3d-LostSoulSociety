/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torch_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:04:16 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/15 14:10:28 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	cleanup_torch_on_error(t_game *game, int i)
{
	while (--i >= 0)
		mlx_destroy_image(game->mlx, game->torch_frames[i]);
	free(game->torch_frames);
	free(game->torch_buffers);
	game->torch_frames = NULL;
	game->torch_buffers = NULL;
}

static int	load_torch_frame(t_game *game, char *path, int i)
{
	void	*img_ptr;
	int		width;
	int		height;

	img_ptr = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!img_ptr)
		return (0);
	game->torch_frames[i] = img_ptr;
	game->torch_buffers[i] = (int *)mlx_get_data_addr(img_ptr,
			&game->bits_per_pixel, &game->torch_line_lengths[i],
			&game->endian);
	if (i == 0)
	{
		game->torch_w = width;
		game->torch_h = height;
	}
	return (1);
}

static void	init_torch_paths(char **frames)
{
	frames[0] = "textures/frame1.xpm";
	frames[1] = "textures/frame2.xpm";
	frames[2] = "textures/frame3.xpm";
	frames[3] = "textures/frame4.xpm";
}

static int	allocate_torch_memory(t_game *game)
{
	game->torch_frame_count = 0;
	game->torch_frames = malloc(sizeof(void *) * 4);
	game->torch_buffers = malloc(sizeof(int *) * 4);
	if (!game->torch_frames || !game->torch_buffers)
		return (0);
	return (1);
}

void	load_torch_animation(t_game *game)
{
	char	*frames[4];
	int		i;

	init_torch_paths(frames);
	if (!allocate_torch_memory(game))
		return ;
	i = 0;
	while (i < 4)
	{
		if (!load_torch_frame(game, frames[i], i))
		{
			cleanup_torch_on_error(game, i);
			return ;
		}
		game->torch_frame_count++;
		i++;
	}
	game->current_frame = 0;
	game->last_frame_time = time(NULL);
}
