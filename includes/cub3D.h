/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:43:27 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/15 22:33:06 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>
#include <math.h>
#include "../libft/inc/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define ESC_KEY 53
#define A_KEY 0
#define D_KEY 2
#define W_KEY 13
#define S_KEY 1
#define LEFT_KEY 123
#define RIGHT_KEY 124
#define UP_KEY 126
#define DOWN_KEY 125

#define PI 3.14159265359
#define TWO_PI 6.28318530718

#define MINIMAP_SCALE_FACTOR 1

#define TILE_SIZE 64

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 820

#define FOV_ANGLE (60 * (PI / 180))
#define MINIMAP_SCALE 0.25
#define WALL_STRIP_WIDTH 1
#define NUM_RAYS WINDOW_WIDTH

typedef struct s_img
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int width;
	int height;
} t_img;

typedef struct s_sprites
{
	t_img *no;
	t_img *so;
	t_img *we;
	t_img *ea;
} t_sprites;

typedef struct s_player
{
	float x;
	float y;
	float angle;
	int turndir;
	int walkspeed;
	float turnspeed;
	float vertical;
	float horizontal;
} t_player;

typedef struct s_data
{
	void *mlx;
	void *win;

} t_data;

typedef struct s_ray
{
	float rayAngle;
	float wallhitX;
	float wallhitY;
	float distance;
	int wallHitContent;
	int wasHitVertical;
	int is_facing_up;
	int is_facing_down;
	int is_facing_left;
	int is_facing_right;
} t_ray;

typedef struct s_mx
{
	char **map;
	char **map2;
	int height;
	int width;
	int count;
	int print;
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	int h;
	float p_dir;
	char *F;
	char *f;
	int i;
	int j;
	float x;
	float y;
	int map2_height;
} t_mx;

typedef struct s_cub
{
	t_data *data;
	t_player *player;
	t_img *img;
	t_img *texture;
	t_sprites *sprit;
	t_ray *ray[NUM_RAYS];
	t_mx *mx;
	int is_ray_facing_down;
	int is_ray_facing_up;
	int is_ray_facing_right;
	int is_ray_facing_left;
	float horzWallHitX;
	float horzWallHitY;
	int horzWallContent;
	float vertWallHitX;
	float vertWallHitY;
	int vertWallContent;
	float xintercept;
	float yintercept;
	float xstep;
	float ystep;
} t_cub;

void file_checker(char *str);
void parsing_map(t_mx *mlx, char *av);
void exit_str(char *str);
void exit_success(char *str);
void exit_error(char *str, char *err);
void exit_strerr(char *str, int err);

// void render_map(t_cub *cub);
// void render_player(t_cub *cub);

//////////////////
void if_edentifier_is_null(t_mx *mlx);
void check_colors(t_mx *mlx);
int check_identifier_extension(t_mx *mlx);
int check_identifier_format(char **identifier);

void check_walls(t_mx *mlx);

/////////////////

void clear_sceen(t_cub *cub);
int set_defeult(int keycode, t_cub *cub);
int key_hook(int keycode, t_cub *cub);
int distroy_event(int keycode, t_cub *cub);
int map_has_wall_at(float x, float y, t_cub *cub);
void move_player(t_cub *cub);

//////////////////////////
void generate_projection(t_cub *cub, t_ray **rays);
void cast_all_rays(t_cub *cub);
void my_mlx_pixel_put(t_img *img, int x, int y, int color);
// void init_textures(t_cub *cub);

unsigned int	get_pixel_from_image(t_img *img, int x, int y);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	move_player(t_cub *cub);
float	find_vertical_wall_hit(t_ray **rays, int stripId, t_cub *cub);
void	calculate_vertical_intersection(float rayAngle, t_cub *cub);
void	calculate_horizontal_intersection(float rayAngle, t_cub *cub);
t_img	*get_dir(t_cub *cub, int x);
float	distance_between_points(float x1, float y1, float x2, float y2);
float	normalize_angle(float angle);
void	calculate_ray_direction(float rayAngle, t_cub *cub);
float	find_horizontal_wall_hit(t_ray **rays, int stripId, t_cub *cub);
#endif
