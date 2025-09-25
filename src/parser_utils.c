/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by fabi              #+#    #+#             */
/*   Updated: 2025/09/16 02:07:24 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	free_lines(char **lines, int count)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (i < count)
		free(lines[i++]);
	free(lines);
}

int	is_map_line(char *line)
{
	int	i;

	if (!line || !*line)
		return (0);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || line[i] == '\n')
		return (0);
	return (line[i] == '1' || line[i] == '0');
}

void	extract_map_from_lines(t_game *game, char **lines, int count)
{
	int	i;
	int	max_width;

	if (count <= 0)
		return ;
	max_width = 0;
	i = 0;
	while (i < count)
	{
		if ((int)ft_strlen(lines[i]) > max_width)
			max_width = ft_strlen(lines[i]);
		i++;
	}
	game->map_width = max_width;
	allocate_and_fill_map(game, lines);
}
