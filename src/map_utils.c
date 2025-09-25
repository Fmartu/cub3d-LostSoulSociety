/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by fabi              #+#    #+#             */
/*   Updated: 2025/09/16 01:58:33 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	find_player_position(t_game *game, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				*x = j;
				*y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	calculate_map_dimensions(t_game *game)
{
	int	i;
	int	len;

	game->map_width = 0;
	i = 0;
	while (i < game->map_height)
	{
		len = ft_strlen(game->map[i]);
		if (len > game->map_width)
			game->map_width = len;
		i++;
	}
}

int	validate_texture_path(char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

char	*get_map_char_at(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map_height)
		return (NULL);
	if (x < 0 || x >= (int)ft_strlen(game->map[y]))
		return (NULL);
	return (&game->map[y][x]);
}

int	is_position_valid(t_game *game, int x, int y)
{
	char	*map_char;

	map_char = get_map_char_at(game, x, y);
	if (!map_char)
		return (0);
	return (*map_char == '0' || *map_char == 'N' || *map_char == 'S'
		|| *map_char == 'E' || *map_char == 'W' || *map_char == 'D');
}
