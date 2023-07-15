/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 10:08:30 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/14 17:56:52 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	setup(t_cub *cub)
{
	clear_sceen(cub);
	move_player(cub);
	cast_all_rays(cub);
	generate3DProjection(cub, cub->ray);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win,
		cub->img->img, 0, 0);
	return (0);
}
t_img	*new_sprite(void *mlx, char *path)
{
	t_img	*sprite;

	sprite = malloc(sizeof(t_img));
	if (!sprite)
		exit_strerr("malloc", errno);
	sprite->img = mlx_xpm_file_to_image(mlx, path,
			&sprite->width, &sprite->height);
	if (!sprite->img)
		exit_strerr(path, errno);
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel,
			&sprite->line_length, &sprite->endian);
	return (sprite);
}

void	init_texture(t_cub *cub)
{
	cub->sprit->no = new_sprite(cub->data->mlx, cub->mx->NO);
	cub->sprit->so = new_sprite(cub->data->mlx, cub->mx->SO);
	cub->sprit->we = new_sprite(cub->data->mlx, cub->mx->WE);
	cub->sprit->ea = new_sprite(cub->data->mlx, cub->mx->EA);
}


void	initialize(t_cub *cub)
{
	int	i;

	i = -1;
	cub->data = malloc(sizeof(t_data));
	cub->player = malloc(sizeof(t_player));
	while (i < NUM_RAYS)
		cub->ray[i++] = malloc(sizeof(t_ray));
	if (!cub->data || !cub->player)
		exit_strerr("malloc", errno);
	cub->data->mlx = mlx_init();
	if (!cub->data->mlx)
		exit_error("mlx_init", "Error initializing MLX");
	cub->data->win = mlx_new_window(cub->data->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!cub->data->win)
		exit_error("mlx_new_window", "Error creating MLX window");
	cub->img = malloc(sizeof(t_img));
	if (!cub->img)
		exit_strerr("malloc", errno);
	cub->img->img = mlx_new_image(cub->data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
			&cub->img->line_length, &cub->img->endian);
	init_texture(cub);
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		exit_success("Usage: ./cub3D <map.cub>");
	cub = (t_cub *)malloc(sizeof(t_cub));
	cub->mx = malloc(sizeof(t_mx));
	parsing_map(cub->mx, av[1]);
	initialize(cub);
	cub->player->x = (cub->mx->y * TILE_SIZE) + 32;
	cub->player->y = (cub->mx->x * TILE_SIZE) + 32;
	cub->player->angle = PI/2;
	cub->player->turndir = 0;
	cub->player->horizontal = 0;
	cub->player->vertical = 0;
	cub->player->turnspeed = 8 * (PI / 180);
	cub->player->walkspeed = 15;
	mlx_hook(cub->data->win, 2, 0, key_hook, cub);
	mlx_hook(cub->data->win, 3, 0, set_defeult, cub);
	mlx_hook(cub->data->win, 17, 0, distroy_event, cub);
	mlx_loop_hook(cub->data->mlx, setup, cub);
	mlx_loop(cub->data->mlx);
}
