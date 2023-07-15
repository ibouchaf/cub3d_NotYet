/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:31:45 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/09 12:49:11 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	if_edentifier_is_null(t_mx *mlx)
{
	if (mlx->NO == NULL || mlx->SO == NULL
		|| mlx->WE == NULL || mlx->EA == NULL
		|| mlx->F == NULL || mlx->f == NULL)
		ft_putstr("Errors In Map \n");
}

int	height_map2(t_mx *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mlx->height > i)
	{
		if (ft_strncmp(mlx->map[i], mlx->NO, 2) == 0
			|| ft_strncmp(mlx->map[i], mlx->SO, 2) == 0
			|| ft_strncmp(mlx->map[i], mlx->WE, 2) == 0
			|| ft_strncmp(mlx->map[i], mlx->EA, 2) == 0
			|| ft_strncmp(mlx->map[i], mlx->F, 1) == 0
			|| ft_strncmp(mlx->map[i], mlx->f, 1) == 0
			|| mlx->map[i][j] == '\n')
				i++;
		else
			return (i);
	}
	return (i);
}

void	is_surrounded_by_walls(t_mx	*mlx)
{
	mlx->i = 0;
	mlx->j = -1;
	while (mlx->map2[0][++mlx->j] != '\n')
	{
		if (mlx->map2[0][mlx->j] != '1' && mlx->map2[0][mlx->j] != ' ')
			ft_putstr("Not surrender by walls \n");
	}
	mlx->j = -1;
	while (mlx->map2[mlx->map2_height - 1][++mlx->j] != '\n')
	{
		if (mlx->map2[mlx->height][mlx->j] != '1'
			&& mlx->map2[mlx->height][mlx->j] != ' ')
			ft_putstr("Not surrender by walls \n");
	}
	mlx->i = 0;
	while (mlx->height > mlx->i - 1)
	{
		// -2 cuz it calcule /0 and j start with 0 also
		mlx->j = ft_strlen(mlx->map2[mlx->i]) - 2;
		if (mlx->map2[mlx->i][mlx->j] != '1'
			&& mlx->map2[mlx->i][mlx->j] != ' ')
			ft_putstr("Not surrender by waalls \n");
		mlx->i++;
	}
}

void	complete_map(t_mx *mlx)
{
	int z;
	int p = 0;
	int found_empty_line = 0;
	char *tmp;
	int	i;

	i = 0;
	while (mlx->map2_height > i)
	{
		tmp = ft_strtrim(mlx->map[mlx->j], " ");
		if (ft_strcmp(tmp, "\n") && ft_strcmp(tmp, ""))
		{
			if (found_empty_line)
				exit(69);
			mlx->map2[mlx->i++] = mlx->map[mlx->j];
		}
		else
			found_empty_line = 1;
		mlx->j++;
		free(tmp);
		i++;
	}
	mlx->h = mlx->i;
	mlx->map2[mlx->i] = NULL;
	i = 0;
	while (mlx->map2[i])
	{
		z = 0;
		while (mlx->map2[i][z])
		{
			if (mlx->map2[i][z] == 'N')
			{
				mlx->x = i;
				mlx->y = z;
			}
			if (mlx->map2[i][z] != '0'  && mlx->map2[i][z] != 32  && mlx->map2[i][z] != '\n' && mlx->map2[i][z] != '1'  && mlx->map2[i][z] != 'N'  && mlx->map2[i][z] != 'S'  &&mlx->map2[i][z] != 'E'  && mlx->map2[i][z] != 'W')
				ft_putstr("kayna chi haja mn ghir player\n");
			if (mlx->map2[i][z] == 'N' || mlx->map2[i][z] == 'S'
				|| mlx->map2[i][z] == 'E' || mlx->map2[i][z] == 'W')
				p++;
			z++;
		}
		i++;
	}
	if (p != 1)
		ft_putstr("Errors in player\n");
	mlx->height = mlx->i - 1;// cuz i contain null.
}

void	check_walls(t_mx *mlx)
{
	int	i;

	i = -1;
	mlx->j = height_map2(mlx);
	mlx->map2_height = mlx->height - mlx->j;
	mlx->map2 = malloc(sizeof(char *) * (mlx->map2_height + 1));
	while (++i < mlx->map2_height)
		mlx->map2[i] = NULL;
	mlx->i = 0;
	complete_map(mlx);
	is_surrounded_by_walls(mlx);
	mlx->i = 1;
	while (mlx->map2_height > mlx->i + 1)
	{
		printf("%d\n", mlx->i);
		mlx->j = 0;
		while (mlx->map2[mlx->i][mlx->j])
		{
			if (mlx->map2[mlx->i][mlx->j] == '0'
				|| mlx->map2[mlx->i][mlx->j] == 'N')
			{
				if (mlx->j > (int)ft_strlen(mlx->map2[mlx->i + 1])
					|| mlx->j > (int)ft_strlen(mlx->map2[mlx->i - 1])
					|| mlx->j == 0)
					ft_putstr("Player can't go outside");
				if (mlx->map2[mlx->i][mlx->j - 1] == ' '
					|| mlx->map2[mlx->i][mlx->j - 1] == '\n'
					|| mlx->map2[mlx->i][mlx->j + 1] == ' '
					|| mlx->map2[mlx->i][mlx->j + 1] == '\n'
					|| mlx->map2[mlx->i - 1][mlx->j] == ' '
					|| mlx->map2[mlx->i - 1][mlx->j] == '\n'
					|| mlx->map2[mlx->i + 1][mlx->j] == ' '
					|| mlx->map2[mlx->i + 1][mlx->j] == '\n')
					ft_putstr("Errors in map \n");
			}
			mlx->j++;
		}
		mlx->i++;
	}
}
