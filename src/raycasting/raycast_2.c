/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:49:09 by ael-bako          #+#    #+#             */
/*   Updated: 2023/07/23 09:01:14 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_facing(int facing)
{
	if (facing)
		return (-1);
	return (0);
}

float	find_vertical_wall_hit(t_ray **rays, int stripId, t_cub *cub)
{
	int		found_vert_wall_hit;
	float	x_to_check;
	float	y_to_check;
	float	vert_hit_distance;

	found_vert_wall_hit = FALSE;
	while ((cub->xintercept) >= 0
		&& (cub->xintercept) <= (cub->mx->width * TILE_SIZE)
		&& (cub->yintercept) >= 0
		&& (cub->yintercept) <= (cub->mx->height * TILE_SIZE))
	{
		x_to_check = (cub->xintercept) + is_facing(cub->is_ray_facing_left);
		y_to_check = (cub->yintercept);
		if (map_has_wall_at(x_to_check, y_to_check, cub))
		{
			cub->vertwallhit_x = (cub->xintercept);
			cub->vertwallhit_y = (cub->yintercept);
			found_vert_wall_hit = TRUE;
			break ;
		}
		else
		{
			(cub->xintercept) += cub->xstep;
			(cub->yintercept) += cub->ystep;
		}
	}
	if (found_vert_wall_hit)
		vert_hit_distance = distance_between_points(cub->player->x,
				cub->player->y, cub->vertwallhit_x, cub->vertwallhit_y);
	else
		vert_hit_distance = INT_MAX;
	return (vert_hit_distance);
}

void	calculate_vertical_intersection(float ray_angle, t_cub *cub)
{
	cub->xintercept = floor(cub->player->x / TILE_SIZE) * TILE_SIZE;
	if (cub->is_ray_facing_right)
		cub->xintercept += TILE_SIZE;
	cub->yintercept = cub->player->y
		+ (cub->xintercept - cub->player->x) * tan(ray_angle);
	cub->xstep = TILE_SIZE;
	if (cub->is_ray_facing_left)
		cub->xstep *= -1;
	cub->ystep = TILE_SIZE * tan(ray_angle);
	if (cub->is_ray_facing_up && (cub->ystep > 0))
		cub->ystep *= -1;
	if (cub->is_ray_facing_down && (cub->ystep < 0))
		cub->ystep *= -1;
}

float	find_horizontal_wall_hit(t_ray **rays, int stripId, t_cub *cub)
{
	int		found_horz_wall_hit;
	float	x_to_check;
	float	y_to_check;
	float	hor_hit_distance;

	found_horz_wall_hit = FALSE;
	cub->horzwallhit_x = 0;
	cub->horzwallhit_y = 0;
	cub->horzWallContent = 0;
	while ((cub->xintercept) >= 0
		&& (cub->xintercept) <= (cub->mx->width * TILE_SIZE)
		&& (cub->yintercept) >= 0
		&& (cub->yintercept) <= (cub->mx->height * TILE_SIZE))
	{
		x_to_check = (cub->xintercept);
		y_to_check = (cub->yintercept) + is_facing(cub->is_ray_facing_up);
		if (map_has_wall_at(x_to_check, y_to_check, cub))
		{
			cub->horzwallhit_x = (cub->xintercept);
			cub->horzwallhit_y = (cub->yintercept);
			found_horz_wall_hit = TRUE;
			break ;
		}
		else
		{
			(cub->xintercept) += cub->xstep;
			(cub->yintercept) += cub->ystep;
		}
	}
	if (found_horz_wall_hit)
		hor_hit_distance = distance_between_points(cub->player->x,
				cub->player->y, cub->horzwallhit_x, cub->horzwallhit_y);
	else
		hor_hit_distance = INT_MAX;
	return (hor_hit_distance);
}

void	calculate_horizontal_intersection(float ray_angle, t_cub *cub)
{
	cub->yintercept = floor(cub->player->y / TILE_SIZE) * TILE_SIZE;
	if (cub->is_ray_facing_down)
		cub->yintercept += TILE_SIZE;
	cub->xintercept = cub->player->x
		+ (cub->yintercept - cub->player->y) / tan(ray_angle);
	cub->ystep = TILE_SIZE;
	if (cub->is_ray_facing_up)
		cub->ystep *= -1;
	cub->xstep = TILE_SIZE / tan(ray_angle);
	if ((cub->is_ray_facing_left && (cub->xstep > 0)))
		cub->xstep *= -1;
	if ((cub->is_ray_facing_right && (cub->xstep < 0)))
		cub->xstep *= -1;
}
