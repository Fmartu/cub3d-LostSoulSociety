/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extraction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:00:00 by fmartusc          #+#    #+#             */
/*   Updated: 2025/01/20 10:00:00 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	fill_map_row(t_game *game, char **lines, int i)
{
	int	j;
	int	line_len;

	line_len = ft_strlen(lines[i]);
	j = 0;
	while (j < line_len && j < game->map_width)
	{
		game->map[i][j] = lines[i][j];
		j++;
	}
	while (j < game->map_width)
	{
		game->map[i][j] = ' ';
		j++;
	}
	game->map[i][game->map_width] = '\0';
}

void	allocate_and_fill_map(t_game *game, char **lines)
{
	int	i;

	game->map = malloc(sizeof(char *) * game->map_height);
	game->door_states = malloc(sizeof(int *) * game->map_height);
	if (!game->map || !game->door_states)
		exit(1);
	i = 0;
	while (i < game->map_height)
	{
		game->map[i] = malloc(sizeof(char) * (game->map_width + 1));
		game->door_states[i] = malloc(sizeof(int) * game->map_width);
		if (!game->map[i] || !game->door_states[i])
			exit(1);
		fill_map_row(game, lines, i);
		initialize_door_states(game, i);
		i++;
	}
}
