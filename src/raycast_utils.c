/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:53:12 by fabi              #+#    #+#             */
/*   Updated: 2025/09/16 02:20:26 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	calculate_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->pos_y) * ray->delta_dist_y;
	}
}

void	clamp_map_x(t_game *game, t_ray *ray)
{
	if (ray->map_x < 0)
		ray->map_x = 0;
	else if (ray->map_x >= game->map_width)
		ray->map_x = game->map_width - 1;
}

void	clamp_map_y(t_game *game, t_ray *ray)
{
	if (ray->map_y < 0)
		ray->map_y = 0;
	else if (ray->map_y >= game->map_height)
		ray->map_y = game->map_height - 1;
}
