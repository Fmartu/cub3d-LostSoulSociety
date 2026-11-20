/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/16 02:07:50 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	parse_texture(t_game *game, char *identifier, char *path)
{
	if (ft_strncmp(identifier, "NO", 2) == 0 && !game->tex_north_path)
		game->tex_north_path = ft_strdup(path);
	else if (ft_strncmp(identifier, "SO", 2) == 0 && !game->tex_south_path)
		game->tex_south_path = ft_strdup(path);
	else if (ft_strncmp(identifier, "WE", 2) == 0 && !game->tex_west_path)
		game->tex_west_path = ft_strdup(path);
	else if (ft_strncmp(identifier, "EA", 2) == 0 && !game->tex_east_path)
		game->tex_east_path = ft_strdup(path);
	else
		return (0);
	return (1);
}

static int	parse_color(t_game *game, char *identifier, char *color)
{
	if (ft_strncmp(identifier, "F", 1) == 0 && !game->floor_color)
		game->floor_color = ft_strdup(color);
	else if (ft_strncmp(identifier, "C", 1) == 0 && !game->ceiling_color)
		game->ceiling_color = ft_strdup(color);
	else
		return (0);
	return (1);
}

int	parse_config_line(t_game *game, char *line)
{
	char	**parts;
	int		result;

	parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1])
	{
		if (parts)
			free_split(parts);
		return (0);
	}
	result = 0;
	if (parse_texture(game, parts[0], parts[1]))
		result = 1;
	else if (parse_color(game, parts[0], parts[1]))
		result = 1;
	free_split(parts);
	return (result);
}
