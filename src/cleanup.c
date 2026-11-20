/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:03:42 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/15 14:04:31 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	free_map(t_game *game)
{
	int	i;

	if (!game->map)
		return ;
	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i])
			free(game->map[i]);
		if (game->door_states && game->door_states[i])
			free(game->door_states[i]);
		i++;
	}
	free(game->map);
	free(game->door_states);
	game->map = NULL;
	game->door_states = NULL;
	game->map_width = 0;
	game->map_height = 0;
}

static void	free_timer_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 11)
	{
		if (game->timer_textures[i])
			mlx_destroy_image(game->mlx, game->timer_textures[i]);
		i++;
	}
}

static void	free_start_textures(t_game *game)
{
	if (game->tex_start)
		mlx_destroy_image(game->mlx, game->tex_start);
	if (game->tex_start2)
		mlx_destroy_image(game->mlx, game->tex_start2);
}

void	free_textures(t_game *game)
{
	void	*textures[8];
	int		i;

	textures[0] = game->tex_north;
	textures[1] = game->tex_south;
	textures[2] = game->tex_east;
	textures[3] = game->tex_west;
	textures[4] = game->tex_door;
	textures[5] = game->tex_sticker;
	textures[6] = game->tex_end;
	textures[7] = NULL;
	i = 0;
	while (textures[i])
	{
		mlx_destroy_image(game->mlx, textures[i]);
		i++;
	}
	free_timer_textures(game);
	free_start_textures(game);
	free_torch_animation(game);
}

void	free_game(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	free_textures(game);
	free_map(game);
	cleanup_audio(game);
	get_next_line_cleanup();
	if (game->mlx)
		free(game->mlx);
	exit(0);
}
