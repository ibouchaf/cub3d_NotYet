/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:49:48 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/15 08:48:19 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	get_pixel_from_image(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x
			* (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || y >= WINDOW_HEIGHT
		|| x >= WINDOW_WIDTH)
		return ;
	dst = img->addr + (y * img->line_length + x
			* (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

void	move_player(t_cub *cub)
{
	float	move_step_ver;
	float	move_step_hor;
	float	xstep;
	float	ystep;

	xstep = 0;
	ystep = 0;
	cub->player->angle += cub->player->turndir * cub->player->turnspeed;
	move_step_ver = cub->player->vertical * cub->player->walkspeed;
	move_step_hor = cub->player->horizontal * cub->player->walkspeed;
	xstep += (cos(cub->player->angle) * move_step_ver);
	xstep += (cos(cub->player->angle + PI / 2) * move_step_hor);
	ystep += (sin(cub->player->angle) * move_step_ver);
	ystep += (sin(cub->player->angle + PI / 2) * move_step_hor);
	xstep *= 5;
	ystep *= 5;
	if (!map_has_wall_at(cub->player->x + xstep, cub->player->y + ystep, cub))
	{
		cub->player->x += xstep / 5;
		cub->player->y += ystep / 5;
	}
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float find_vertical_wall_hit(t_ray **rays, int stripId, t_cub *cub)
{
	int		foundVertWallHit;
	float	xToCheck;
	float	yToCheck;

	foundVertWallHit = FALSE;
	while ((cub->xintercept) >= 0 && (cub->xintercept) <= (34 * TILE_SIZE)
		&& (cub->yintercept) >= 0 && (cub->yintercept) <= (cub->mx->h * TILE_SIZE))
	{
		xToCheck = (cub->xintercept) + (cub->isRayFacingLeft ? -1 : 0);
		yToCheck = (cub->yintercept);
		if (map_has_wall_at(xToCheck, yToCheck, cub))
		{
			cub->vertWallHitX = (cub->xintercept);
			cub->vertWallHitY = (cub->yintercept);
			foundVertWallHit = TRUE;
			break ;
		}
		else
		{
			(cub->xintercept) += cub->xstep;
			(cub->yintercept) += cub->ystep;
		}
	}
	float vertHitDistance = foundVertWallHit
		? distance_between_points(cub->player->x, cub->player->y, cub->vertWallHitX, cub->vertWallHitY)
		: INT_MAX;
	return (vertHitDistance);
}

void calculate_vertical_intersection(float rayAngle, t_cub* cub)
{
	cub->xintercept = floor(cub->player->x / TILE_SIZE) * TILE_SIZE;
	if (cub->isRayFacingRight)
		cub->xintercept += TILE_SIZE;
	cub->yintercept = cub->player->y
		+ (cub->xintercept - cub->player->x) * tan(rayAngle);
	cub->xstep = TILE_SIZE;
	if (cub->isRayFacingLeft)
		cub->xstep *= -1;
	cub->ystep = TILE_SIZE * tan(rayAngle);
	if (cub->isRayFacingUp && (cub->ystep > 0))
		cub->ystep *= -1;
	if (cub->isRayFacingDown && (cub->ystep < 0))
		cub->ystep *= -1;
}

float find_horizontal_wall_hit(t_ray **rays, int stripId, t_cub *cub)
{
	int	foundHorzWallHit;
	float xToCheck;
	float yToCheck;

	foundHorzWallHit = FALSE;
	cub->horzWallHitX = 0;
	cub->horzWallHitY = 0;
	cub->horzWallContent = 0;
	while ((cub->xintercept) >= 0 && (cub->xintercept) <= (34 * TILE_SIZE)
		&& (cub->yintercept) >= 0 && (cub->yintercept) <= (cub->mx->h * TILE_SIZE))
	{
		xToCheck = (cub->xintercept);
		yToCheck = (cub->yintercept) + (cub->isRayFacingUp ? -1 : 0);
		if (map_has_wall_at(xToCheck, yToCheck, cub))
		{
			cub->horzWallHitX = (cub->xintercept);
			cub->horzWallHitY = (cub->yintercept);
			foundHorzWallHit = TRUE;
			break ;
		}
		else
		{
			(cub->xintercept) += cub->xstep;
			(cub->yintercept) += cub->ystep;
		}
	}
	float horzHitDistance = foundHorzWallHit
		? distance_between_points(cub->player->x, cub->player->y, cub->horzWallHitX, cub->horzWallHitY)
		: INT_MAX;
	return (horzHitDistance);
}

void calculate_horizontal_intersection(float rayAngle, t_cub *cub)
{
	cub->yintercept = floor(cub->player->y / TILE_SIZE) * TILE_SIZE;
	if (cub->isRayFacingDown)
		cub->yintercept += TILE_SIZE;
	cub->xintercept = cub->player->x
		+ (cub->yintercept - cub->player->y) / tan(rayAngle);
	cub->ystep = TILE_SIZE;
	if (cub->isRayFacingUp)
		cub->ystep *= -1;
	cub->xstep = TILE_SIZE / tan(rayAngle);
	if ((cub->isRayFacingLeft && (cub->xstep > 0)))
		cub->xstep *= -1;
	if ((cub->isRayFacingRight && (cub->xstep < 0)))
		cub->xstep *= -1;
}

void calculate_ray_direction(float rayAngle, t_cub *cub)
{
	(cub->isRayFacingDown) = (rayAngle > 0 && rayAngle < PI);
	(cub->isRayFacingUp) = !((cub->isRayFacingDown));
	(cub->isRayFacingRight) = (rayAngle < 0.5 * PI || rayAngle > 1.5 * PI);
	(cub->isRayFacingLeft) = !((cub->isRayFacingRight));
}

void cast_ray(float rayAngle, int stripId, t_ray **rays, t_cub *cub)
{
	rayAngle = normalize_angle(rayAngle);
	// float 	xintercept,yintercept, xstep, ystep;
	float 	horzHitDistance;
	float	vertHitDistance;

	calculate_ray_direction(rayAngle, cub);
	calculate_horizontal_intersection(rayAngle, cub);
	horzHitDistance = find_horizontal_wall_hit(rays, stripId, cub);
	calculate_vertical_intersection(rayAngle, cub);
	vertHitDistance = find_vertical_wall_hit(rays, stripId, cub);
	// // Calculate both horizontal and vertical hit distances and choose the smallest one

	if (vertHitDistance < horzHitDistance)
	{
		rays[stripId]->distance = vertHitDistance;
		rays[stripId]->wallhitX = cub->vertWallHitX;
		rays[stripId]->wallhitY = cub->vertWallHitY;
		rays[stripId]->wallHitContent = cub->vertWallContent;
		rays[stripId]->wasHitVertical = TRUE;
	}
	else
	{
		rays[stripId]->distance = horzHitDistance;
		rays[stripId]->wallhitX = cub->horzWallHitX;
		rays[stripId]->wallhitY = cub->horzWallHitY;
		rays[stripId]->wallHitContent = cub->horzWallContent;
		rays[stripId]->wasHitVertical = FALSE;
	}
	rays[stripId]->rayAngle = rayAngle;
	rays[stripId]->is_facing_down = cub->isRayFacingDown;
	rays[stripId]->is_facing_up = cub->isRayFacingUp;
	rays[stripId]->is_facing_left = cub->isRayFacingLeft;
	rays[stripId]->is_facing_right = cub->isRayFacingRight;
}

void	cast_all_rays(t_cub *cub)
{
	float	ray_angle;
	int		stripid;

	stripid = 0;
	ray_angle = cub->player->angle - (FOV_ANGLE / 2);
	while (stripid < NUM_RAYS)
	{
		cast_ray(ray_angle, stripid, cub->ray, cub);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		stripid++;
	}
}

int get_dir(t_cub *cub, int x)
{
	if (cub->ray[x]->wasHitVertical && cub->ray[x]->is_facing_left)
		return (0);
	else if (cub->ray[x]->wasHitVertical && cub->ray[x]->is_facing_right)
		return (1);
	else if (!cub->ray[x]->wasHitVertical && cub->ray[x]->is_facing_up)
		return (2);
	return (3);
}

void rect(t_cub *cub, int x, int y, int width, int height)
{
	int		i;
	int		j;
	int		tex_x;
	int		tex_y;
	float	scale1;
	float	scale2;

	i = 0;
	if (!get_dir(cub, x))
		cub->texture = cub->sprit->we;
	else if (get_dir(cub, x) == 1)
		cub->texture = cub->sprit->so;
	else if (get_dir(cub, x) == 2)
		cub->texture = cub->sprit->no;
	else
		cub->texture = cub->sprit->ea;
	scale1 = cub->texture->width / TILE_SIZE;
	tex_x = cub->ray[x]->wallhitX;
	if (cub->ray[x]->wasHitVertical)
		tex_x = cub->ray[x]->wallhitY;
	tex_x = fmod(((float)tex_x * scale1), cub->texture->width);
	scale2 = ((double)cub->texture->height / height);
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			if ((y + j) >= WINDOW_HEIGHT)
				break ;
			tex_y = (float) j * scale2;
			my_mlx_pixel_put(cub->img, x + i, y + j, get_pixel_from_image(cub->texture, tex_x, tex_y));
			j++;
		}
		i++;
	}
}

void	generate3DProjection(t_cub *cub, t_ray **rays)
{
	int		i;
	float	perp_distance;
	float	dis_proj_lane;
	float	projected_wall_height;
	int		wall_top_pixel;

	i = 0;
	while (i < NUM_RAYS)
	{
		perp_distance = rays[i]->distance * cos(rays[i]->rayAngle
				- cub->player->angle);
		dis_proj_lane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		projected_wall_height = (TILE_SIZE / perp_distance) * dis_proj_lane;
		wall_top_pixel = (WINDOW_HEIGHT / 2) - ((int)projected_wall_height / 2);
		rect(cub, i * WALL_STRIP_WIDTH, wall_top_pixel, 1,
			(int)projected_wall_height);
		i++;
	}
}
