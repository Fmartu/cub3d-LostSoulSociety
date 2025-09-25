/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_map_parser_fixed.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:00:00 by fabi              #+#    #+#             */
/*   Updated: 2025/01/18 10:00:00 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == 'D');
}

int	is_valid_map_line(char *line)
{
	int	i;
	int	has_content;

	if (!line)
		return (0);
	has_content = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		{
			if (is_valid_map_char(line[i]))
				has_content = 1;
			else
				return (0);
		}
		i++;
	}
	return (has_content);
}

static void	init_texture_paths(t_game *game)
{
	game->tex_north_path = NULL;
	game->tex_south_path = NULL;
	game->tex_east_path = NULL;
	game->tex_west_path = NULL;
	game->floor_color = NULL;
	game->ceiling_color = NULL;
}

void	parse_error(void)
{
	write(2, "Error: Cannot open map file\n", 28);
	exit(1);
}

void	parse_map(t_game *game, const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		parse_error();
	init_texture_paths(game);
	parse_and_store_config(game, fd);
	close(fd);
}
