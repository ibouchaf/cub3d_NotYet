/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:49:09 by ael-bako          #+#    #+#             */
/*   Updated: 2023/07/15 22:22:38 by ael-bako         ###   ########.fr       */
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
		&& (cub->yintercept) <= (cub->mx->h * TILE_SIZE))
	{
		x_to_check = (cub->xintercept) + is_facing(cub->is_ray_facing_left);
		y_to_check = (cub->yintercept);
		if (map_has_wall_at(x_to_check, y_to_check, cub))
		{
			cub->vertWallHitX = (cub->xintercept);
			cub->vertWallHitY = (cub->yintercept);
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
				cub->player->y, cub->vertWallHitX, cub->vertWallHitY);
	else
		vert_hit_distance = INT_MAX;
	return (vert_hit_distance);
}

void	calculate_vertical_intersection(float rayAngle, t_cub *cub)
{
	cub->xintercept = floor(cub->player->x / TILE_SIZE) * TILE_SIZE;
	if (cub->is_ray_facing_right)
		cub->xintercept += TILE_SIZE;
	cub->yintercept = cub->player->y
		+ (cub->xintercept - cub->player->x) * tan(rayAngle);
	cub->xstep = TILE_SIZE;
	if (cub->is_ray_facing_left)
		cub->xstep *= -1;
	cub->ystep = TILE_SIZE * tan(rayAngle);
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
	cub->horzWallHitX = 0;
	cub->horzWallHitY = 0;
	cub->horzWallContent = 0;
	while ((cub->xintercept) >= 0
		&& (cub->xintercept) <= (cub->mx->width * TILE_SIZE)
		&& (cub->yintercept) >= 0
		&& (cub->yintercept) <= (cub->mx->h * TILE_SIZE))
	{
		x_to_check = (cub->xintercept);
		y_to_check = (cub->yintercept) + is_facing(cub->is_ray_facing_up);
		if (map_has_wall_at(x_to_check, y_to_check, cub))
		{
			cub->horzWallHitX = (cub->xintercept);
			cub->horzWallHitY = (cub->yintercept);
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
				cub->player->y, cub->horzWallHitX, cub->horzWallHitY);
	else
		hor_hit_distance = INT_MAX;
	return (hor_hit_distance);
}

void	calculate_horizontal_intersection(float rayAngle, t_cub *cub)
{
	cub->yintercept = floor(cub->player->y / TILE_SIZE) * TILE_SIZE;
	if (cub->is_ray_facing_down)
		cub->yintercept += TILE_SIZE;
	cub->xintercept = cub->player->x
		+ (cub->yintercept - cub->player->y) / tan(rayAngle);
	cub->ystep = TILE_SIZE;
	if (cub->is_ray_facing_up)
		cub->ystep *= -1;
	cub->xstep = TILE_SIZE / tan(rayAngle);
	if ((cub->is_ray_facing_left && (cub->xstep > 0)))
		cub->xstep *= -1;
	if ((cub->is_ray_facing_right && (cub->xstep < 0)))
		cub->xstep *= -1;
}
