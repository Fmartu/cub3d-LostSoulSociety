/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:00:00 by fabi              #+#    #+#             */
/*   Updated: 2025/09/20 13:59:01 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	handle_remaining_line(char **first_map_line, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n");
	if (trimmed && *trimmed && is_map_line(trimmed) && !*first_map_line)
		*first_map_line = ft_strdup(line);
	free(trimmed);
	free(line);
}

static void	process_config_line(t_game *game, char *line, char **first_map_line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n");
	if (trimmed && *trimmed)
	{
		if (is_map_line(trimmed) && !*first_map_line)
		{
			*first_map_line = ft_strdup(line);
			free(trimmed);
			return ;
		}
		if (!*first_map_line)
			parse_config_line(game, trimmed);
	}
	free(trimmed);
}

static char	*read_config_lines(t_game *game, int fd)
{
	char	*line;
	char	*first_map_line;
	int		result;

	first_map_line = NULL;
	result = get_next_line(fd, &line);
	while (result > 0)
	{
		process_config_line(game, line, &first_map_line);
		free(line);
		if (first_map_line)
			break ;
		result = get_next_line(fd, &line);
	}
	if (result == 0 && line)
		handle_remaining_line(&first_map_line, line);
	return (first_map_line);
}

void	parse_and_store_config(t_game *game, int fd)
{
	char	*first_map_line;

	first_map_line = read_config_lines(game, fd);
	if (first_map_line)
	{
		read_complete_map(game, fd, first_map_line);
		free(first_map_line);
	}
}
