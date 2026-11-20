/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_map_parser_helpers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:00:00 by fmartusc          #+#    #+#             */
/*   Updated: 2025/01/20 10:00:00 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static char	**allocate_temp_map(int capacity)
{
	char	**temp_map;

	temp_map = malloc(sizeof(char *) * capacity);
	if (!temp_map)
		exit(1);
	return (temp_map);
}

static void	process_first_line(t_game *game, char **temp_map, char *first_line)
{
	if (first_line && is_valid_map_line(first_line))
	{
		temp_map[game->map_height] = ft_strdup(first_line);
		game->map_height++;
	}
}

static void	process_line_loop(t_game *game, char **temp_map, int fd,
		int capacity)
{
	char	*line;
	int		result;

	result = get_next_line(fd, &line);
	while (result > 0)
	{
		if (game->map_height >= capacity - 1)
		{
			printf("Map too large, stopping at %d lines\n", game->map_height);
			free(line);
			break ;
		}
		temp_map[game->map_height] = line;
		game->map_height++;
		result = get_next_line(fd, &line);
	}
	if (result == 0 && line && *line)
	{
		temp_map[game->map_height] = line;
		game->map_height++;
	}
	else if (line)
		free(line);
}

void	read_complete_map(t_game *game, int fd, char *first_line)
{
	char	**temp_map;
	int		capacity;

	capacity = 100;
	temp_map = allocate_temp_map(capacity);
	game->map_height = 0;
	process_first_line(game, temp_map, first_line);
	process_line_loop(game, temp_map, fd, capacity);
	temp_map[game->map_height] = NULL;
	extract_map_from_lines(game, temp_map, game->map_height);
	free_lines(temp_map, game->map_height);
}
