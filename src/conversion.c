/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:28:21 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/16 02:09:53 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	free_end_texture(t_game *game)
{
	if (game->tex_end)
	{
		mlx_destroy_image(game->mlx, game->tex_end);
		game->tex_end = NULL;
		game->buf_end = NULL;
	}
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	if (!str)
		return (0);
	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

void	draw_square(t_game *game, int *params, int size, int color)
{
	int	row;
	int	col;

	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			if (params[0] + col >= 0 && params[0] + col < WIN_W
				&& params[1] + row >= 0 && params[1] + row < WIN_H)
			{
				*(int *)(game->addr + ((params[1] + row) * game->line_length
							+ (params[0] + col) * (game->bits_per_pixel / 8)))
					= color;
			}
			col++;
		}
		row++;
	}
}
