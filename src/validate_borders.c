/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_borders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:00:00 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/20 13:57:52 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	is_border_cell(t_game *game, int i, int j)
{
	return (i == 0 || i == game->map_height - 1
		|| j == 0 || j >= (int)ft_strlen(game->map[i]) - 1);
}

static int	check_border_position(t_game *game, int i, int j)
{
	if (is_border_cell(game, i, j))
	{
		if (game->map[i][j] != '1')
		{
			write(2, "Error: Map not surrounded by walls\n", 36);
			return (0);
		}
	}
	return (1);
}

static int	has_adjacent_space(t_game *game, int i, int j)
{
	if (i > 0 && (j >= (int)ft_strlen(game->map[i - 1])
			|| game->map[i - 1][j] == ' '))
		return (1);
	if (i < game->map_height - 1 && (j >= (int)ft_strlen(game->map[i + 1])
			|| game->map[i + 1][j] == ' '))
		return (1);
	if (j > 0 && game->map[i][j - 1] == ' ')
		return (1);
	if (j < (int)ft_strlen(game->map[i]) - 1 && game->map[i][j + 1] == ' ')
		return (1);
	return (0);
}

static int	check_adjacent_spaces(t_game *game, int i, int j)
{
	if (has_adjacent_space(game, i, j))
	{
		write(2, "Error: Map has holes\n", 21);
		return (0);
	}
	return (1);
}

int	check_map_borders(t_game *game, char **visited)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width && j < (int)ft_strlen(game->map[i]))
		{
			if (visited[i][j] == '1')
			{
				if (!check_border_position(game, i, j))
					return (0);
				if (!check_adjacent_spaces(game, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
