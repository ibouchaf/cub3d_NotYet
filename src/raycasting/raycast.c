/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:49:48 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/16 18:32:01 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	assign_hor_ver_ray(t_ray **rays, int stripId,
	float distance, t_cub *cub)
{
	if (stripId > 0)
	{
		rays[stripId]->distance = distance;
		rays[stripId]->wallhitX = cub->vertWallHitX;
		rays[stripId]->wallhitY = cub->vertWallHitY;
		rays[stripId]->wallHitContent = cub->vertWallContent;
		rays[stripId]->wasHitVertical = TRUE;
	}
	else
	{
		stripId = stripId * -1;
		rays[stripId]->distance = distance;
		rays[stripId]->wallhitX = cub->horzWallHitX;
		rays[stripId]->wallhitY = cub->horzWallHitY;
		rays[stripId]->wallHitContent = cub->horzWallContent;
		rays[stripId]->wasHitVertical = FALSE;
	}
}

void	cast_ray(float rayAngle, int stripId, t_ray **rays, t_cub *cub)
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
		assign_hor_ver_ray(rays, stripId, vert_hit_distance, cub);
	else
		assign_hor_ver_ray(rays, stripId * -1, horz_hit_distance, cub);
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

void	render_ceiling(t_cub *cub, int x, int y, int width, int height)
{
	int		i[2];

	i[0] = -1;
	while (++i[0] < width)
	{
		i[1] = -1;
		while (++i[1] < height)
		{
			my_mlx_pixel_put(cub->img, x + i[0], y + i[1],
				cub->mx->color1);
		}
	}
}
void	render_floor(t_cub *cub, int x, int y, int width, int height)
{
	int		i[2];

	i[0] = -1;
	while (++i[0] < width)
	{
		i[1] = -1;
		while (++i[1] < height)
		{
			my_mlx_pixel_put(cub->img, x + i[0], y + i[1],
				cub->mx->color2);
		}
	}
}


void	rect(t_cub *cub, int x, int y, int width, int height)
{
	int		i[2];
	int		tex[2];
	float	scale[2];
	unsigned int color;

	i[0] = -1;
	cub->texture = get_dir(cub, x);
	scale[0] = cub->texture->width / TILE_SIZE;
	tex[0] = cub->ray[x]->wallhitX;
	if (cub->ray[x]->wasHitVertical)
		tex[0] = cub->ray[x]->wallhitY;
	tex[0] = fmod(((float)tex[0] * scale[0]), cub->texture->width);
	scale[1] = ((double)cub->texture->height / height);
	while (++i[0] < width)
	{
		i[1] = -1;
		while (++i[1] < height)
		{
			if ((y + i[1]) >= WINDOW_HEIGHT)
				break ;
			tex[1] = (float) i[1] * scale[1];
			my_mlx_pixel_put(cub->img, x + i[0], y + i[1],
				get_pixel_from_image(cub->texture, tex[0], tex[1]));
		}
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
	render_ceiling(cub, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 2);
	render_floor(cub, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT);
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
