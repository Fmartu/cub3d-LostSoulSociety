/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_flood.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:00:00 by fmartusc          #+#    #+#             */
/*   Updated: 2025/01/20 10:00:00 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	flood_fill(t_game *game, char **visited, int x, int y)
{
	char	c;

	if (y < 0 || y >= game->map_height || x < 0 || x >= game->map_width)
		return ;
	if (visited[y][x] == '1')
		return ;
	if (x >= (int)ft_strlen(game->map[y]))
		return ;
	c = game->map[y][x];
	if (c == '1' || c == ' ')
		return ;
	if (visited[y][x] == '1')
		return ;
	visited[y][x] = '1';
	flood_fill(game, visited, x + 1, y);
	flood_fill(game, visited, x - 1, y);
	flood_fill(game, visited, x, y + 1);
	flood_fill(game, visited, x, y - 1);
}

static char	**create_visited_map(t_game *game)
{
	char	**visited;
	int		i;
	int		j;

	visited = malloc(sizeof(char *) * game->map_height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		visited[i] = malloc(sizeof(char) * game->map_width);
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		j = 0;
		while (j < game->map_width)
			visited[i][j++] = '0';
		i++;
	}
	return (visited);
}

static void	free_visited_map(char **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

static int	check_doors_reachable(t_game *game, char **visited)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < (int)ft_strlen(game->map[i]))
		{
			if (game->map[i][j] == 'D')
			{
				if (visited[i][j] != '1')
				{
					write(2, "Error: Unreachable door in map\n", 32);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_flood_fill(t_game *game)
{
	char	**visited;
	int		player_x;
	int		player_y;

	if (!find_player_position(game, &player_x, &player_y))
		return (0);
	visited = create_visited_map(game);
	if (!visited)
		return (0);
	flood_fill(game, visited, player_x, player_y);
	if (!check_doors_reachable(game, visited))
	{
		free_visited_map(visited, game->map_height);
		return (0);
	}
	if (!check_map_borders(game, visited))
	{
		free_visited_map(visited, game->map_height);
		return (0);
	}
	free_visited_map(visited, game->map_height);
	return (1);
}
