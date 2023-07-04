/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:43:27 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/04 15:05:05 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include "../libft/inc/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define TRUE 1
# define FALSE 0

# define ESC_KEY 53
# define A_KEY 0
# define D_KEY 2
# define W_KEY 13
# define S_KEY 1
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define UP_KEY 126
# define DOWN_KEY 125

# define PI 3.14159265359
# define TWO_PI 6.28318530718

# define TILE_SIZE 64
# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20

# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

# define FOV_ANGLE (60 * (PI / 180))

# define WALL_STRIP_WIDTH 4
# define NUM_RAYS (WINDOW_WIDTH / WALL_STRIP_WIDTH)

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_player {
	float	x;
	float	y;
	float	angle;
	int		turndir;
	int		walkdir;
	float	turnspeed;
	float	walkspeed;
}	t_player;

typedef struct s_data {
	void	*mlx;
	void	*win;

}	t_data;

typedef struct s_cub {
	t_data		*data;
	t_player	*player;
	t_img		*img;
}	t_cub;

typedef struct s_ray {
	float	rayAngle;
	float	wallhitX;
	float	wallhitY;
	float	distance;
	int		wasHitVertical;
	int		is_facing_up;
	int		is_facing_down;
	int		is_facing_left;
	int		is_facing_right;
}	t_ray;

void	parsing(char *str);
void	file_checker(char *str);

void	exit_str(char *str);
void	exit_success(char *str);
void	exit_error(char *str, char *err);
void	exit_strerr(char *str, int err);

void	render_map(t_cub *cub);
void	render_player(t_cub *cub);

#endif
