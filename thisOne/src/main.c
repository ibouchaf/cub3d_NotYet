/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 10:08:30 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/10 19:04:29 by ael-bako         ###   ########.fr       */
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

void	init_texture(t_cub *cub, int i)
{
	cub->texture = malloc(sizeof(t_img));
	if (cub->ray[i]->is_facing_down)
		cub->texture->img = mlx_xpm_file_to_image(cub->data->mlx,
				"./pikuma.xpm", &cub->texture->width, &cub->texture->height);
	else if (cub->ray[i]->is_facing_up)
		cub->texture->img = mlx_xpm_file_to_image(cub->data->mlx,
				"./graystone.xpm", &cub->texture->width, &cub->texture->height);
	else if (cub->ray[i]->wasHitVertical)
		cub->texture->img = mlx_xpm_file_to_image(cub->data->mlx,
				"./redbrick.xpm", &cub->texture->width, &cub->texture->height);
	else
		cub->texture->img = mlx_xpm_file_to_image(cub->data->mlx,
				"./wood.xpm", &cub->texture->width, &cub->texture->height);
	if (!cub->texture->img)
		exit(0);
	cub->texture->addr = mlx_get_data_addr(cub->texture->img,
			&cub->texture->bits_per_pixel,
			&cub->texture->line_length, &cub->texture->endian);
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
	init_texture(cub, 0);
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
	cub->player->angle = PI / 2;
	cub->player->turndir = 0;
	cub->player->walkdir = 0;
	cub->player->turnspeed = 5 * (PI / 180);
	cub->player->walkspeed = 10;
	mlx_hook(cub->data->win, 2, 0, key_hook, cub);
	mlx_hook(cub->data->win, 3, 0, set_defeult, cub);
	mlx_hook(cub->data->win, 17, 0, distroy_event, cub);
	mlx_loop_hook(cub->data->mlx, setup, cub);
	mlx_loop(cub->data->mlx);
}
