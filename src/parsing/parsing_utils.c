/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 08:26:53 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/23 09:05:04 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_range(char **str)
{
	if ((ft_atoi(str[0]) < 0 || ft_atoi(str[0]) > 255)
		|| (ft_atoi(str[1]) < 0 || ft_atoi(str[1]) > 255)
		|| (ft_atoi(str[2]) < 0 || ft_atoi(str[2]) > 255))
		return (1);
	return (0);
}

int	is_number(char **str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (is_range(str))
		return (1);
	while (str[i])
	{
		tmp = ft_strtrim(str[i], " \t");
		j = 0;
		while (tmp[j] && tmp[j] != '\n')
		{
			if (!ft_isdigit(tmp[j]))
				return (1);
			j++;
		}
		free(tmp);
		i++;
	}
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

int	ft_comma(char *s)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = 0;
	tmp = ft_strtrim(s, " \t\n");
	if (!ft_isdigit(tmp[0]))
		return (0);
	while (tmp[i])
	{
		if (tmp[i] == ',')
			len++;
		i++;
	}
	free(tmp);
	return (len);
}

void	check_colors(t_mx *mlx)
{
	char	**color1;
	char	**color2;

	if (ft_comma(mlx->F) != 2 || ft_comma(mlx->f) != 2)
		ft_putstr("Errors In Colors\n");
	color1 = ft_split(mlx->F, ',');
	color2 = ft_split(mlx->f, ',');
	if (is_number(color1) == 1 || is_number(color2) == 1)
		ft_putstr("Errors In Colors\n");
	free_tab(color1);
	free_tab(color2);
}
