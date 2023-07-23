/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 08:45:56 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/23 08:44:26 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_free(char **s, int *i)
{
	while (*i >= 0)
	{
		free(s[*i]);
		(*i)--;
	}
	free(s);
}

void	check_extension(int ac, char *str)
{
	int		i;
	char	**s;

	i = 0;
	if (ac != 2)
		ft_putstr("invalid argument");
	else
	{
		s = ft_split(str, '.');
		while (s[i])
			i++;
		if (ft_strncmp(s[i - 1], "cub", 4) == 0)
		{
			ft_free(s, &i);
			return ;
		}
		else
		{
			ft_free(s, &i);
			write(2, "Error\n", 6);
			ft_putstr("The Map Doesn't end with .cub");
		}
	}
}

int	rgb_to_decimal(char *s)
{
	char	**color;
	int		red;
	int		green;
	int		blue;
	int		decimal_value;

	color = ft_split(s, ',');
	red = ft_atoi(color[0]);
	green = ft_atoi(color[1]);
	blue = ft_atoi(color[2]);
	decimal_value = (red << 16) + (green << 8) + blue;
	free_tab(color);
	return (decimal_value);
}

void	if_edentifier_is_null(t_mx *mlx)
{
	if (mlx->NO == NULL || mlx->SO == NULL
		|| mlx->WE == NULL || mlx->EA == NULL
		|| mlx->F == NULL || mlx->f == NULL)
		ft_putstr("Errors In Map \n");
}
