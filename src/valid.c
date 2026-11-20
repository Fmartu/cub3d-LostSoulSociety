/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/18 22:23:38 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static int	is_valid_number(char *str)
{
	int	i;
	int	val;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	val = ft_atoi(str);
	return (val >= 0 && val <= 255);
}

static int	validate_rgb_components(char **rgb)
{
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (0);
	if (!is_valid_number(rgb[0]))
		return (0);
	if (!is_valid_number(rgb[1]))
		return (0);
	if (!is_valid_number(rgb[2]))
		return (0);
	return (1);
}

static int	validate_color_format(char *color_str)
{
	char	**rgb;
	int		i;
	int		result;

	if (!color_str)
		return (0);
	rgb = ft_split(color_str, ',');
	if (!rgb)
		return (0);
	result = validate_rgb_components(rgb);
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
	return (result);
}

int	validate_colors(t_game *game)
{
	if (!validate_color_format(game->floor_color)
		|| !validate_color_format(game->ceiling_color))
	{
		write(2, "Error\nInvalid color format\n", 28);
		return (0);
	}
	return (1);
}
