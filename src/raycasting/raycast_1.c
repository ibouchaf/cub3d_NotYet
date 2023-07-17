/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:46:42 by ael-bako          #+#    #+#             */
/*   Updated: 2023/07/17 09:09:09 by ael-bako         ###   ########.fr       */
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
	xstep *= 1.5;
	ystep *= 1.5;
	if (!map_has_wall_at(cub->player->x + xstep, cub->player->y + ystep, cub))
	{
		cub->player->x += xstep / 1.5;
		cub->player->y += ystep / 1.5;
	}
}
