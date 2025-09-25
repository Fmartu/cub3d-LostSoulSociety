/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_initialization_fixed.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:00:00 by fabi              #+#    #+#             */
/*   Updated: 2025/01/18 10:00:00 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	count_doors_in_row(t_game *game, int i)
{
	int	j;
	int	door_count;

	door_count = 0;
	j = 0;
	while (j < game->map_width && j < (int)ft_strlen(game->map[i]))
	{
		if (game->map[i][j] == 'D')
			door_count++;
		j++;
	}
	return (door_count);
}

static void	check_and_set_doors(t_game *game)
{
	int	i;
	int	door_count;

	door_count = 0;
	i = 0;
	while (i < game->map_height)
	{
		door_count += count_doors_in_row(game, i);
		i++;
	}
	if (door_count > 0)
		game->has_doors = 1;
}

static void	init_all_door_states(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		initialize_door_states(game, i);
		i++;
	}
}

void	initialize_all_doors(t_game *game)
{
	game->has_doors = 0;
	check_and_set_doors(game);
	init_all_door_states(game);
}

int	verify_textures_loaded(t_game *game)
{
	if (!game->buf_north || !game->buf_south
		|| !game->buf_east || !game->buf_west)
		return (0);
	if (game->has_doors && !game->buf_door)
		return (0);
	return (1);
}
