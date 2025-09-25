/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:00:00 by fabi              #+#    #+#             */
/*   Updated: 2025/09/20 13:57:12 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	free_rgb_array(char **rgb)
{
	int	i;

	if (!rgb)
		return ;
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}

static int	validate_rgb_range(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

static int	parse_rgb_color(char *color_str, int *r, int *g, int *b)
{
	char	**rgb;

	if (!color_str)
		return (0);
	rgb = ft_split(color_str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_rgb_array(rgb);
		return (0);
	}
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	free_rgb_array(rgb);
	return (validate_rgb_range(*r, *g, *b));
}

int	convert_colors(t_game *game)
{
	int	r;
	int	g;
	int	b;

	if (!parse_rgb_color(game->floor_color, &r, &g, &b))
	{
		write(2, "Error: Invalid floor color format\n", 35);
		return (0);
	}
	game->floor_rgb = (r << 16) | (g << 8) | b;
	if (!parse_rgb_color(game->ceiling_color, &r, &g, &b))
	{
		write(2, "Error: Invalid ceiling color format\n", 37);
		return (0);
	}
	game->ceiling_rgb = (r << 16) | (g << 8) | b;
	return (1);
}
