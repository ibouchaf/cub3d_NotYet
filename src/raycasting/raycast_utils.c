/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:50:53 by ael-bako          #+#    #+#             */
/*   Updated: 2023/07/17 11:03:22 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_img	*get_dir(t_cub *cub, int x)
{
	if (cub->ray[x]->wasHitVertical && cub->ray[x]->is_facing_left)
		return (cub->sprit->we);
	else if (cub->ray[x]->wasHitVertical && cub->ray[x]->is_facing_right)
		return (cub->sprit->ea);
	else if (!cub->ray[x]->wasHitVertical && cub->ray[x]->is_facing_up)
		return (cub->sprit->no);
	return (cub->sprit->so);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

void	calculate_ray_direction(float rayAngle, t_cub *cub)
{
	(cub->is_ray_facing_down) = (rayAngle > 0 && rayAngle < PI);
	(cub->is_ray_facing_up) = !((cub->is_ray_facing_down));
	(cub->is_ray_facing_right) = (rayAngle < 0.5 * PI || rayAngle > 1.5 * PI);
	(cub->is_ray_facing_left) = !((cub->is_ray_facing_right));
}
