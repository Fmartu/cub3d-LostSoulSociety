/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:00:00 by fabi              #+#    #+#             */
/*   Updated: 2025/09/18 22:53:56 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	validate_textures(t_game *game)
{
	if (!validate_texture_path(game->tex_north_path)
		|| !validate_texture_path(game->tex_south_path)
		|| !validate_texture_path(game->tex_east_path)
		|| !validate_texture_path(game->tex_west_path))
	{
		write(2, "Error: Invalid texture paths\n", 30);
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	int	i;

	if (!validate_textures(game))
		return (0);
	if (!validate_colors(game))
		return (0);
	if (!convert_colors(game))
		return (0);
	if (!validate_map_complete(game))
		return (0);
	if (game->has_doors)
	{
		i = 0;
		while (i < game->map_height)
		{
			initialize_door_states(game, i);
			i++;
		}
	}
	return (1);
}
