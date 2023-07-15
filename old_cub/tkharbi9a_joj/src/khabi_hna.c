/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   khabi_hna.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 08:27:39 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/09 13:59:16 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_identifier(t_mx *mlx, int i)
{
	if (ft_strncmp(mlx->map[i], "NO ", 3) == 0)
		return ((mlx->NO = mlx->map[i]), 1);
	else if (ft_strncmp(mlx->map[i], "SO ", 3) == 0)
		return ((mlx->SO = mlx->map[i]), 1);
	else if (ft_strncmp(mlx->map[i], "WE ", 3) == 0)
		return ((mlx->WE = mlx->map[i]), 1);
	else if (ft_strncmp(mlx->map[i], "EA ", 3) == 0)
		return ((mlx->EA = mlx->map[i]), 1);
	else if (ft_strncmp(mlx->map[i], "F ", 2) == 0)
		return ((mlx->F = mlx->map[i]), 1);
	else if (ft_strncmp(mlx->map[i], "C ", 2) == 0)
		return ((mlx->f = mlx->map[i]), 1);
	return (0);
}

void	count_height(t_mx **mlx, int fd)
{
	char	*str;

	str = NULL;
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		(*mlx)->height++;
	}
}

void	init(t_mx *mlx)
{
	mlx->map2 = NULL;
	mlx->NO = NULL;
	mlx->SO = NULL;
	mlx->WE = NULL;
	mlx->EA = NULL;
	mlx->F = NULL;
	mlx->f = NULL;
	mlx->height = 0;
	mlx->width = 0;
	mlx->count = 0;
	mlx->map = NULL;
}

void	parsing_map(t_mx *mlx, char *av)
{
	int	fd;
	int i = 0;
	int j = 0;
	int k = 0;

	init(mlx);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		ft_putstr("no such file or directory");
	count_height(&mlx, fd);
	mlx->map = malloc(sizeof(char *) * (mlx->height + 1));
	fd = open(av, O_RDONLY);
	while (mlx->height > i)
		mlx->map[i++] = get_next_line(fd);
	mlx->map[i] = NULL;
	i = -1;
	while (mlx->height > ++i)
	{
		if (check_identifier(mlx, i))
			mlx->count++;
		else if (mlx->map[i][j] == '\n')
			k++;
		else
		{
			if (mlx->count != 6)
				ft_putstr("Errors In Edentifier \n");
			if_edentifier_is_null(mlx);
		}
	}
	check_colors(mlx);
	if (!check_identifier_format(ft_split(mlx->NO, ' '))
		|| !check_identifier_format(ft_split(mlx->SO, ' '))
		|| !check_identifier_format(ft_split(mlx->WE, ' '))
		|| !check_identifier_format(ft_split(mlx->EA, ' ')))
		ft_putstr("Errors in Identifier Format\n");
	if (!check_identifier_extension(mlx))
		ft_putstr("Identifiers do not end with .xpm\n");
	check_walls(mlx);
}
