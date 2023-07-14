/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:49:48 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/14 13:31:09 by ael-bako         ###   ########.fr       */
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

float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void cast_ray(float rayAngle, int stripId, t_ray **rays, t_cub *cub) {
	rayAngle = normalize_angle(rayAngle);

	int isRayFacingDown = rayAngle > 0 && rayAngle < PI;
	int isRayFacingUp = !isRayFacingDown;

	int isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
	int isRayFacingLeft = !isRayFacingRight;

	float xintercept, yintercept;
	float xstep, ystep;

	///////////////////////////////////////////
	// HORIZONTAL RAY-GRID INTERSECTION CODE
	///////////////////////////////////////////
	int foundHorzWallHit = FALSE;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	int horzWallContent = 0;

	// Find the y-coordinate of the closest horizontal grid intersection
	yintercept = floor(cub->player->y / TILE_SIZE) * TILE_SIZE;
	yintercept += isRayFacingDown ? TILE_SIZE : 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	xintercept = cub->player->x + (yintercept - cub->player->y) / tan(rayAngle);

	// Calculate the increment xstep and ystep
	ystep = TILE_SIZE;
	ystep *= isRayFacingUp ? -1 : 1;

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	// Increment xstep and ystep until we find a wall
	while (nextHorzTouchX >= 0 && nextHorzTouchX <= (34 * TILE_SIZE) && nextHorzTouchY >= 0 && nextHorzTouchY <= (cub->mx->h * TILE_SIZE)) {
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

		if (map_has_wall_at(xToCheck, yToCheck, cub)) {
			// found a wall hit
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			// horzWallContent = cub->mx->map2[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
			foundHorzWallHit = TRUE;
			break;
		} else {
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}
	///////////////////////////////////////////
	// VERTICAL RAY-GRID INTERSECTION CODE
	///////////////////////////////////////////
	int foundVertWallHit = FALSE;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int vertWallContent = 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	xintercept = floor(cub->player->x / TILE_SIZE) * TILE_SIZE;
	xintercept += isRayFacingRight ? TILE_SIZE : 0;

	// Find the y-coordinate of the closest horizontal grid intersection
	yintercept = cub->player->y + (xintercept - cub->player->x) * tan(rayAngle);

	// Calculate the increment xstep and ystep
	xstep = TILE_SIZE;
	xstep *= isRayFacingLeft ? -1 : 1;

	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
	ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	// // Increment xstep and ystep until we find a wall
	while (nextVertTouchX >= 0 && nextVertTouchX <= (34 * TILE_SIZE) && nextVertTouchY >= 0 && nextVertTouchY <= (cub->mx->h * TILE_SIZE)) {
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (map_has_wall_at(xToCheck, yToCheck, cub)) {
			// found a wall hit
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			// vertWallContent = cub->mx->map2[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
			foundVertWallHit = TRUE;
			break;
		} else {
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}

	// // Calculate both horizontal and vertical hit distances and choose the smallest one
	float horzHitDistance = foundHorzWallHit
		? distanceBetweenPoints(cub->player->x, cub->player->y, horzWallHitX, horzWallHitY)
		: INT_MAX;
	float vertHitDistance = foundVertWallHit
		? distanceBetweenPoints(cub->player->x, cub->player->y, vertWallHitX, vertWallHitY)
		: INT_MAX;

	if (vertHitDistance < horzHitDistance)
	{
		rays[stripId]->distance = vertHitDistance;
		rays[stripId]->wallhitX = vertWallHitX;
		rays[stripId]->wallhitY = vertWallHitY;
		rays[stripId]->wallHitContent = vertWallContent;
		rays[stripId]->wasHitVertical = TRUE;
	}
	else
	{
		rays[stripId]->distance = horzHitDistance;
		rays[stripId]->wallhitX = horzWallHitX;
		rays[stripId]->wallhitY = horzWallHitY;
		rays[stripId]->wallHitContent = horzWallContent;
		rays[stripId]->wasHitVertical = FALSE;
	}
	rays[stripId]->rayAngle = rayAngle;
	rays[stripId]->is_facing_down = isRayFacingDown;
	rays[stripId]->is_facing_up = isRayFacingUp;
	rays[stripId]->is_facing_left = isRayFacingLeft;
	rays[stripId]->is_facing_right = isRayFacingRight;
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

	// exit(0);
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
	tex_x = fmod((tex_x * scale1), cub->texture->width);
	scale2 = ((double)cub->texture->height / height);
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			if ((y + j) >= WINDOW_HEIGHT)
				break ;
			tex_y = j * scale2;
			my_mlx_pixel_put(cub->img, x + i, y + j,
				get_pixel_from_image(cub->texture, tex_x, tex_y));
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
		// init_texture(cub, i);
		rect(cub, i * WALL_STRIP_WIDTH, wall_top_pixel, 1,
			(int)projected_wall_height);
		i++;
	}
}
