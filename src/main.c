/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 10:08:30 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/04 15:09:30 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

const int	map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int	distroy_event(int keycode, t_cub *cub)
{
	(void)cub;
	(void)keycode;
	exit(0);
	return (0);
}

int	is_onwall(t_cub *cub, float x, float y)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	(void)cub;
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	return (map[map_grid_index_y][map_grid_index_x] != 0);
}

void my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char *dst;

	dst = cub->img->addr + (y * (MAP_NUM_COLS * TILE_SIZE * 4) + x * 4);
	*(unsigned int *)dst = color;
}


void	my_pixel_put(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put(cub, x + i, y + j, color);
			j++;
		}
		i++;
	}
}


void	render_map(t_cub *cub)
{
	int		i;
	int		j;
	int		tilex;
	int		tiley;

	j = 0;
	while (j < MAP_NUM_ROWS)
	{
		i = 0;
		while (i < MAP_NUM_COLS)
		{
			tilex = i * TILE_SIZE;
			tiley = j * TILE_SIZE;
			if (map[j][i] == 1)
				my_pixel_put(cub, tilex, tiley, 0xDFCD8B);
			else
				my_pixel_put(cub, tilex, tiley, 0xB1B3B2);
			i++;
		}
		j++;
	}
}

void	draw_line(t_cub *cub, int beginx, int beginy,
					int endx, int endy, int color)
{
	int		pixels;
	double	pixelx;
	double	pixely;
	double	deltax;
	double	deltay;

	deltax = endx - beginx;
	deltay = endy - beginy;
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	pixelx = beginx;
	pixely = beginy;
	while (pixels)
	{
		if (is_onwall(cub, pixelx, pixely))
		{
			return ;
		}
		my_mlx_pixel_put(cub, pixelx, pixely, color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
}

void	render_player(t_cub *cub)
{

	my_mlx_pixel_put(cub, cub->player->x, cub->player->y, 0x00203FFF);
	draw_line(cub, cub->player->x, cub->player->y,
		cub->player->x + cos(cub->player->angle) * 70,
		cub->player->y + sin(cub->player->angle) * 70, 0x00203FFF);
}

void	move_player(t_cub *cub)
{
	float	move_step;
	float	new_px;
	float	new_py;

	cub->player->angle += cub->player->turndir * cub->player->turnspeed;
	move_step = cub->player->walkdir * cub->player->walkspeed;
	new_px = cub->player->x + cos(cub->player->angle) * move_step;
	new_py = cub->player->y + sin(cub->player->angle) * move_step;
	if (!is_onwall(cub, new_px, new_py))
	{
		cub->player->x = new_px;
		cub->player->y = new_py;
	}
}

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == ESC_KEY)
		exit(0);
	else if (keycode == W_KEY || keycode == UP_KEY)
		cub->player->walkdir = 1;
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		cub->player->walkdir = -1;
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
		cub->player->turndir = 1;
	else if (keycode == A_KEY || keycode == LEFT_KEY)
		cub->player->turndir = -1;
	move_player(cub);
	return (0);
}

int	set_defeult(int keycode, t_cub *cub)
{
	if (keycode == W_KEY || keycode == UP_KEY
		|| keycode == S_KEY || keycode == DOWN_KEY)
		cub->player->walkdir = 0;
	else if (keycode == D_KEY || keycode == RIGHT_KEY
		|| keycode == A_KEY || keycode == LEFT_KEY)
		cub->player->turndir = 0;
	return (0);
}

void	cast(t_cub *cub)
{
	float rayAngle = cub->player->angle - (FOV_ANGLE/ 2);
	int	stripid = 0;
	while (stripid < NUM_RAYS)
	{
		draw_line(cub, cub->player->x, cub->player->y, cub->player->x + cos(rayAngle) * 70, cub->player->y + sin(rayAngle) * 70, 0xFF00000);
		// cast_ray(rayAngle, stripid);
		rayAngle += FOV_ANGLE / NUM_RAYS;
		stripid++;
	}
}

int	setup(t_cub *cub)
{
	render_map(cub);
	render_player(cub);
	cast(cub);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->img->img, 0, 0);
	return 0;
}

void	initialize(t_cub *cub)
{
	cub->data = malloc(sizeof(t_data));
	cub->player = malloc(sizeof(t_player));
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
}

// void	cast_ray(float rayAngle, int stripid)
// {

// }


int main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		exit_success("Usage: ./cub3D <map.cub>");
	cub = (t_cub *)malloc(sizeof(t_cub));
    parsing(av[1]);
    initialize(cub);
	cub->player->x = WINDOW_WIDTH / 2;
	cub->player->y = WINDOW_HEIGHT / 2;
	cub->player->angle = PI / 2;
	cub->player->turndir = 0;
	cub->player->walkdir = 0;
	cub->player->turnspeed = 20 * (PI / 180);// hadi katwarek ila bghayty tdor lchi blassa bchhal ydour wax bzarba wla gha chwiya
	cub->player->walkspeed = 10;
	mlx_hook(cub->data->win, 2, 0, key_hook, cub);
	mlx_hook(cub->data->win, 3, 0, set_defeult, cub);
	mlx_hook(cub->data->win, 17, 0, distroy_event, cub);
	mlx_loop_hook(cub->data->mlx, setup, cub);
	mlx_loop(cub->data->mlx);
}
