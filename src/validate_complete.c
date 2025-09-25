/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_complete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:00:00 by fabi              #+#    #+#             */
/*   Updated: 2025/09/18 22:56:02 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == 'D' || c == ' '
		|| c == '\n' || c == '\0');
}

static int	check_char_and_count_player(t_game *game, int i, int j, int *count)
{
	char	c;

	c = game->map[i][j];
	if (!is_valid_map_char(c))
	{
		write(2, "Error: Invalid character in map\n", 33);
		return (0);
	}
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(*count)++;
	return (1);
}

static int	validate_map_characters(t_game *game)
{
	int		i;
	int		j;
	int		player_count;

	player_count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < (int)ft_strlen(game->map[i]))
		{
			if (!check_char_and_count_player(game, i, j, &player_count))
				return (0);
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		write(2, "Error: Map must have exactly one player\n", 40);
		return (0);
	}
	return (1);
}

int	validate_map_complete(t_game *game)
{
	if (!validate_map_characters(game))
		return (0);
	if (!validate_flood_fill(game))
		return (0);
	return (1);
}
