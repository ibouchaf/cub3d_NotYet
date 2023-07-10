/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   khabi_hna.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 08:27:39 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/10 19:13:35 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_identifier(t_mx *mlx, int i)
{
	char **str = ft_split(mlx->map[i], ' ');
	if (ft_strncmp(str[0], "NO", 3) == 0 && str[1] && ft_strlen_2(str) == 2)
		return ((mlx->NO = str[1]), 1);
	else if (ft_strncmp(str[0], "SO", 3) == 0 && str[1] && ft_strlen_2(str) == 2)
		return ((mlx->SO = str[1]), 1);
	else if (ft_strncmp(str[0], "WE", 3) == 0 && str[1] && ft_strlen_2(str) == 2)
		return ((mlx->WE = str[1]), 1);
	else if (ft_strncmp(str[0], "EA", 3) == 0 && str[1] && ft_strlen_2(str) == 2)
		return ((mlx->EA = str[1]), 1);
	else if (ft_strncmp(str[0], "F", 2) == 0 && str[1] && ft_strlen_2(str) == 2)
		return ((mlx->F = str[1]), 1);
	else if (ft_strncmp(str[0], "C", 2) == 0 && str[1] && ft_strlen_2(str) == 2)
		return ((mlx->f = str[1]), 1);
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
	// if (!check_identifier_format(ft_split(mlx->NO, ' '))
	// 	|| !check_identifier_format(ft_split(mlx->SO, ' '))
	// 	|| !check_identifier_format(ft_split(mlx->WE, ' '))
	// 	|| !check_identifier_format(ft_split(mlx->EA, ' ')))
	// 	ft_putstr("Errors in Identifier Format\n");
	if (!check_identifier_extension(mlx))
		ft_putstr("Identifiers do not end with .xpm\n");
	check_walls(mlx);
}
