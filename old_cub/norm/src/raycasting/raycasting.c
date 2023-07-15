/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:49:48 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/15 10:15:47 by ael-bako         ###   ########.fr       */
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

float	find_vertical_wall_hit(t_ray **rays, int stripId, t_cub *cub)
{
	int		found_vert_wall_hit;
	float	x_to_check;
	float	y_to_check;

	found_vert_wall_hit = FALSE;
	while ((cub->xintercept) >= 0 && (cub->xintercept) <= (cub->mx->width * TILE_SIZE)
		&& (cub->yintercept) >= 0
		&& (cub->yintercept) <= (cub->mx->h * TILE_SIZE))
	{
		x_to_check = (cub->xintercept) + (cub->is_ray_facing_left ? -1 : 0);
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
	float vertHitDistance = found_vert_wall_hit
		? distance_between_points(cub->player->x, cub->player->y, cub->vertWallHitX, cub->vertWallHitY)
		: INT_MAX;
	return (vertHitDistance);
}

void calculate_vertical_intersection(float rayAngle, t_cub* cub)
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

float find_horizontal_wall_hit(t_ray **rays, int stripId, t_cub *cub)
{
	int		found_horz_wall_hit;
	float	x_to_check;
	float	y_to_check;

	found_horz_wall_hit = FALSE;
	cub->horzWallHitX = 0;
	cub->horzWallHitY = 0;
	cub->horzWallContent = 0;
	while ((cub->xintercept) >= 0 && (cub->xintercept) <= (cub->mx->width * TILE_SIZE)
		&& (cub->yintercept) >= 0
		&& (cub->yintercept) <= (cub->mx->h * TILE_SIZE))
	{
		x_to_check = (cub->xintercept);
		y_to_check = (cub->yintercept) + (cub->is_ray_facing_up ? -1 : 0);
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
	float horzHitDistance = found_horz_wall_hit
		? distance_between_points(cub->player->x, cub->player->y, cub->horzWallHitX, cub->horzWallHitY)
		: INT_MAX;
	return (horzHitDistance);
}

void calculate_horizontal_intersection(float rayAngle, t_cub *cub)
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

void calculate_ray_direction(float rayAngle, t_cub *cub)
{
	(cub->is_ray_facing_down) = (rayAngle > 0 && rayAngle < PI);
	(cub->is_ray_facing_up) = !((cub->is_ray_facing_down));
	(cub->is_ray_facing_right) = (rayAngle < 0.5 * PI || rayAngle > 1.5 * PI);
	(cub->is_ray_facing_left) = !((cub->is_ray_facing_right));
}

void	assign_ray_ver(t_ray **rays, int stripId, float distance, t_cub *cub)
{
	rays[stripId]->distance = distance;
	rays[stripId]->wallhitX = cub->vertWallHitX;
	rays[stripId]->wallhitY = cub->vertWallHitY;
	rays[stripId]->wallHitContent = cub->vertWallContent;
	rays[stripId]->wasHitVertical = TRUE;
}

void	assign_ray_horiz(t_ray **rays, int stripId, float distance, t_cub *cub)
{
	rays[stripId]->distance = distance;
	rays[stripId]->wallhitX = cub->horzWallHitX;
	rays[stripId]->wallhitY = cub->horzWallHitY;
	rays[stripId]->wallHitContent = cub->horzWallContent;
	rays[stripId]->wasHitVertical = FALSE;
}

void cast_ray(float rayAngle, int stripId, t_ray **rays, t_cub *cub)
{
	float		horz_hit_distance;
	float		vert_hit_distance;

	rayAngle = normalize_angle(rayAngle);
	calculate_ray_direction(rayAngle, cub);
	calculate_horizontal_intersection(rayAngle, cub);
	horz_hit_distance = find_horizontal_wall_hit(rays, stripId, cub);
	calculate_vertical_intersection(rayAngle, cub);
	vert_hit_distance = find_vertical_wall_hit(rays, stripId, cub);
	if (vert_hit_distance < horz_hit_distance)
		assign_ray_ver(rays, stripId, vert_hit_distance, cub);
	else
		assign_ray_horiz(rays, stripId, horz_hit_distance, cub);
	rays[stripId]->rayAngle = rayAngle;
	rays[stripId]->is_facing_down = cub->is_ray_facing_down;
	rays[stripId]->is_facing_up = cub->is_ray_facing_up;
	rays[stripId]->is_facing_left = cub->is_ray_facing_left;
	rays[stripId]->is_facing_right = cub->is_ray_facing_right;
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
			my_mlx_pixel_put(cub->img, x + i, y + j,
				get_pixel_from_image(cub->texture, tex_x, tex_y));
			j++;
		}
		i++;
	}
}

void	generate_projection(t_cub *cub, t_ray **rays)
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
