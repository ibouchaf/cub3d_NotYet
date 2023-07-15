/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 08:26:53 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/15 12:39:54 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_number(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j] && str[i][j] != '\n')
		{
			if ((str[i][j] < '0' || str[i][j] > '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

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
	if (mlx->F[0] < '0' || mlx->F[0] > '9'
		|| mlx->f[0] < '0' || mlx->f[0] > '9')
		ft_putstr("Errors In Colors : starting with comma\n");
	if (ft_strfassila(mlx->F) != 2 || ft_strfassila(mlx->f) != 2)
		ft_putstr("Errors In Colors : check the comma\n");
	color1 = ft_split(mlx->F, ',');
	color2 = ft_split(mlx->f, ',');
	if (is_number(color1) == 1 || is_number(color2) == 1)
		ft_putstr("Color values should be numeric\n");
	if (is_range(color1) || is_range(color2))
		ft_putstr("Color values should be within range\n");
}
