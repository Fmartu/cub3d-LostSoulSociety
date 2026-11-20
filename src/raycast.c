/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:47:42 by fmartusc          #+#    #+#             */
/*   Updated: 2025/09/15 15:12:31 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	check_bounds_and_hit(t_game *game, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= game->map_width
		|| ray->map_y < 0 || ray->map_y >= game->map_height)
	{
		ray->hit = 1;
		clamp_map_x(game, ray);
		clamp_map_y(game, ray);
		return ;
	}
	if (game->map[ray->map_y][ray->map_x] == '1')
		ray->hit = 1;
	else if (game->map[ray->map_y][ray->map_x] == 'D'
		&& !game->door_states[ray->map_y][ray->map_x])
		ray->hit = 1;
}

static void	perform_dda(t_game *game, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		check_bounds_and_hit(game, ray);
	}
}

static void	calculate_texture_x(t_game *game, t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x * (double)game->tex_w);
	if (ray->side == 0 && ray->dir_x < 0)
		ray->tex_x = game->tex_w - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y > 0)
		ray->tex_x = game->tex_w - ray->tex_x - 1;
}

static void	calculate_wall_params(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(WIN_H / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
	if (ray->side == 0)
		ray->wall_x = game->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = game->pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	calculate_texture_x(game, ray);
}

void	raycast_scene(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		init_ray_params(game, x, &ray);
		calculate_step_and_side_dist(game, &ray);
		perform_dda(game, &ray);
		calculate_wall_params(game, &ray);
		draw_wall_column(game, &ray, x, 0);
		x++;
	}
}
