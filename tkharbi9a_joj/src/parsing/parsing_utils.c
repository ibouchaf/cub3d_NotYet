/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 08:26:53 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/09 13:58:28 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int	is_number(char **str)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		j = 0;
// 		while (str[i][j] != '\0')
// 		{
// 			if (str[i][j] <= '0' || str[i][j] >= '9')
// 				return (1);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	is_range(char **str)
{
	if ((ft_atoi(str[0]) < 0 || ft_atoi(str[0]) > 255)
		|| (ft_atoi(str[1]) < 0 || ft_atoi(str[1]) > 255)
		|| (ft_atoi(str[2]) < 0 || ft_atoi(str[2]) > 255))
		return (1);
	return (0);
}

int	check_identifier_format(char **identifier)
{
	if (identifier[2] != NULL)
	{

		return (0);
	}
	if (identifier[1][0] == '\n')
	{

		return (0);
	}
	return (1);
}

int	check_identifier_extension(t_mx *mlx)
{
	if (ft_strncmp(ft_strrchr(mlx->NO, '.'), ".xpm\n", 5) != 0
		|| ft_strncmp(ft_strrchr(mlx->SO, '.'), ".xpm\n", 5) != 0
		|| ft_strncmp(ft_strrchr(mlx->WE, '.'), ".xpm\n", 5) != 0
		|| ft_strncmp(ft_strrchr(mlx->EA, '.'), ".xpm\n", 5) != 0)
	{
		return (0);
	}
	return (1);
}

int	ft_strfassila(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == ',')
			len++;
		i++;
	}
	return (len);
}

void	check_colors(t_mx *mlx)
{
	char	**color1;
	char	**color2;

	color1 = NULL;
	color2 = NULL;
	if (mlx->F[ft_strlen(mlx->F) - 2] < '0'
		|| mlx->F[ft_strlen(mlx->F) - 2] > '9'
		|| mlx->f[ft_strlen(mlx->f) - 2] < '0'
		|| mlx->f[ft_strlen(mlx->f) - 2] > '9')/////////////////if end with ,
		ft_putstr("Errors In Colors : end with comma\n");
	color1 = ft_split(mlx->F, ' ');
	color2 = ft_split(mlx->f, ' ');
	if (color1[2] != NULL || color2[2] != NULL)
		ft_putstr("Errors In Colors : more then 2 argument\n");
	if (color1[1][0] < '0' || color1[1][0] > '9'
		|| color2[1][0] < '0' || color2[1][0] > '9')
		ft_putstr("Errors In Colors : starting with comma\n");
	if (ft_strfassila(color1[1]) != 2 || ft_strfassila(color2[1]) != 2)
		ft_putstr("Errors In Colors : check the comma\n");
	free(color1[0]);
	free(color2[0]);
	char *tmp = color1[1];
	char *tmp2 = color2[1];
	color1 = ft_split(color1[1], ',');
	color2 = ft_split(color2[1], ',');
	free(tmp);
	free(tmp2);
	// if (is_number(color1) == 1 || is_number(color2)  == 1)
	// 	ft_putstr("Color values should be numeric\n");
	if (is_range(color1) || is_range(color2))
		ft_putstr("Color values should be within range\n");
	int	i;

	i = 0;
	while (color1[i])
	{
		free(color1[i]);
		i++;
	}
	i = 0;
	while (color2[i])
	{
		free(color2[i]);
		i++;
	}
	free(color1);
	free(color2);
}
