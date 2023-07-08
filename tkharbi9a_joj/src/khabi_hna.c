#include "cub3D.h"

void	count_height(t_mx **mlx, int fd)
{
	char *str = NULL;

	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		(*mlx)->height++;
	}
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	res;
	int					sign;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - 48;
		if (res >= 9223372036854775807 && sign == 1)
			return (-1);
		if (res > 9223372036854775807 && sign == -1)
			return (0);
	}
	return (res * sign);
}

int ft_strfassila(char *s)
{
    int i = 0;
    int len = 0;
    while (s[i])
    {
        if (s[i] == ',')
            len++;
        i++;
    }
    return (len);
}

int ft_strlen2(char **s)
{
	int i = 0;
	if (!s[i])
		return 0;
	while (s[i])
		i++;
	return i;
}

int	height_map2(t_mx *mlx)
{
	int i = 0;
	int j = 0;
	while(mlx->height > i)
		{
			if (ft_strncmp(mlx->map[i], mlx->a, 2) == 0 || ft_strncmp(mlx->map[i], mlx->b, 2) == 0 ||
				ft_strncmp(mlx->map[i], mlx->c, 2) == 0 || ft_strncmp(mlx->map[i], mlx->d, 2) == 0 ||
				ft_strncmp(mlx->map[i], mlx->e, 1) == 0 || ft_strncmp(mlx->map[i], mlx->f, 1) == 0 ||
				mlx->map[i][j] == '\n')
					i++;
			else
			{
				j = i;
				i = mlx->height;
			}
		}
	return (j);
}
void	init(t_mx *mlx)
{
	mlx->map2 = NULL;
	mlx->a = NULL;
	mlx->b = NULL;
	mlx->c = NULL;
	mlx->d = NULL;
	mlx->e = NULL;
	mlx->f = NULL;
	mlx->height = 0;
	mlx->width = 0;
	mlx->count = 0;
	mlx->map = NULL;
}

void	is_surrounded_by_walls(t_mx	*mlx)
{
	mlx->i = 0;
	mlx->j = 0;

	while(mlx->map2[0][mlx->j] != '\n')
	{
		if(mlx->map2[0][mlx->j] != '1' && mlx->map2[0][mlx->j] != ' ')
			ft_putstr("Not surrender bby walls \n");
		mlx->j++;
	}
	mlx->j = 0;
	while(mlx->map2[mlx->height][mlx->j] != '\n')
	{
		if(mlx->map2[mlx->height][mlx->j] != '1' && mlx->map2[mlx->height][mlx->j] != ' ')
			ft_putstr("Not surrender byyy walls \n");
		mlx->j++;
	}
	mlx->i = 0;
	while(mlx->height > mlx->i - 1)
	{
		mlx->j = ft_strlen(mlx->map2[mlx->i]) - 2;// -2 cuz it calcule /0 and j start with 0 also .
		if (mlx->map2[mlx->i][mlx->j] != '1' && mlx->map2[mlx->i][mlx->j] != ' ')
			ft_putstr("Not surrender by waalls \n");
		mlx->i++;
	}
}

void	complete_map(t_mx *mlx)
{
	int y = 0;
	int z;
	int p = 0;
	int found_empty_line = 0;
	char *tmp;
	while(mlx->height > mlx->j)
	{
		// leaks trim
		tmp = ft_strtrim(mlx->map[mlx->j], " ");
		if(ft_strcmp(tmp, "\n") && ft_strcmp(tmp, ""))
		{
			if (found_empty_line)
				exit(69);
			mlx->map2[mlx->i++] = mlx->map[mlx->j];
		}
		else
			found_empty_line = 1;
		mlx->j++;
		free(tmp);
	}
	mlx->h = mlx->i;
	mlx->map2[mlx->i] = NULL;
	while (mlx->map2[y])
	{
		z = 0;
		while (mlx->map2[y][z])
		{
			if(mlx->map2[y][z] == 'N')
			{
				mlx->x = y;
				mlx->y = z;
			}
			if (mlx->map2[y][z] != '0'  && mlx->map2[y][z] != 32  && mlx->map2[y][z] != '\n' && mlx->map2[y][z] != '1'  && mlx->map2[y][z] != 'N'  && mlx->map2[y][z] != 'S'  &&mlx->map2[y][z] != 'E'  && mlx->map2[y][z] != 'W')
				ft_putstr("kayna chi haja mn ghir player\n");
			if (mlx->map2[y][z] == 'N' ||  mlx->map2[y][z] == 'S' || mlx->map2[y][z] == 'E' || mlx->map2[y][z] == 'W')
				p++;
			z++;
		}
		y++;
	}
	if (p != 1)
		ft_putstr("Errors in player\n");
	mlx->height = mlx->i - 1;// cuz i contain null.
	mlx->i = 1;
}

void	check_walls(t_mx *mlx)
{
	mlx->j = height_map2(mlx);
	mlx->map2 = malloc(sizeof(char *) * (mlx->height - mlx->j + 1));
	for(int i = 0; i < mlx->height - mlx->j + 1; i++)
		mlx->map2[i] = NULL;
	mlx->i = 0;
	complete_map(mlx);
	is_surrounded_by_walls(mlx);
	mlx->i = 1;
	while(mlx->map2[mlx->i + 1]) // no need nt checki line lakhar htach deja checkit wax surronded by walls
	{
		mlx->j = 0;
		while(mlx->map2[mlx->i][mlx->j])
		{
			if (mlx->map2[mlx->i][mlx->j] == '0' || mlx->map2[mlx->i][mlx->j] == 'N')
			{
				if (mlx->j > (int)ft_strlen(mlx->map2[mlx->i + 1])
					|| mlx->j > (int)ft_strlen(mlx->map2[mlx->i - 1]) || mlx->j == 0)
					ft_putstr("Player can't go outside");
				if (mlx->map2[mlx->i][mlx->j - 1] == ' ' || mlx->map2[mlx->i][mlx->j - 1] == '\n'
					|| mlx->map2[mlx->i][mlx->j + 1] == ' ' || mlx->map2[mlx->i][mlx->j + 1] == '\n'
					|| mlx->map2[mlx->i - 1][mlx->j] == ' ' || mlx->map2[mlx->i - 1][mlx->j] == '\n'
					|| mlx->map2[mlx->i + 1][mlx->j] == ' ' || mlx->map2[mlx->i + 1][mlx->j] == '\n')
						ft_putstr("Error in map \n");
			}
			mlx->j++;
		}
		mlx->i++;
	}
}

int	is_number(char **str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while(str[i][j] != '\0')
		{
			if (str[i][j] >= 'a' && str[i][j] <= 'z')
				return(1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_range(char **str)
{
	if ((ft_atoi(str[0]) < 0 || ft_atoi(str[0]) > 255) || (ft_atoi(str[1]) < 0 || ft_atoi(str[1]) > 255)
		 || (ft_atoi(str[2]) < 0 || ft_atoi(str[2]) > 255))
		return (1);
	return(0);
}

int check_identifier(t_mx *mlx, int i)
{
	int j = 0;

	if (mlx->map[i][j] == 'N' && mlx->map[i][j + 1] == 'O' && mlx->map[i][j + 2] == ' ')
	{
		mlx->a = mlx->map[i];
		return 1;
	}
	else if (mlx->map[i][j] == 'S' && mlx->map[i][j + 1] == 'O' && mlx->map[i][j + 2] == ' ')
	{
		mlx->b = mlx->map[i];
		return 1;
	}
	else if (mlx->map[i][j] == 'W' && mlx->map[i][j + 1] == 'E' && mlx->map[i][j + 2] == ' ')
	{
		mlx->c = mlx->map[i];
		return 1;
	}
	else if (mlx->map[i][j] == 'E' && mlx->map[i][j + 1] == 'A' && mlx->map[i][j + 2] == ' ')
	{
		mlx->d = mlx->map[i];
		return 1;
	}
	else if (mlx->map[i][j] == 'F' && mlx->map[i][j + 1] == ' ')
	{
		mlx->e = mlx->map[i];
		return 1;
	}
	else if (mlx->map[i][j] == 'C' && mlx->map[i][j + 1] == ' ')
	{
		mlx->f = mlx->map[i];
		return 1;
	}
	return 0;
}

int check_colors(t_mx *mlx)
{
	char** test1 = NULL;
	char** test2 = NULL;

	if(mlx->e[ft_strlen(mlx->e) - 2] < '0' || mlx->e[ft_strlen(mlx->e) - 2] > '9'
		|| mlx->f[ft_strlen(mlx->f) - 2] < '0' || mlx->f[ft_strlen(mlx->f) - 2] > '9')/////////////////if end with ,
		ft_putstr("Errors In Colors \n");
	test1 = ft_split(mlx->e, ' ');
	test2 = ft_split(mlx->f, ' ');
	if (test1[2] != NULL || test2[2] != NULL)
		ft_putstr("more than 2 in F or C \n");
	if (test1[1][0] < '0' || test1[1][0] > '9' || test2[1][0] < '0' || test2[1][0] > '9')
		ft_putstr("badya b fasila \n");
	if (ft_strrchr(test1[1], ',') != 0 && ft_strrchr(test2[1], ',') != 0)
	{
		if (ft_strfassila(test1[1]) != 2)
			ft_putstr("ktar mn 2 fasilat \n");
		test1 = ft_split(test1[1], ',');
		test2 = ft_split(test2[1], ',');
	}
	else
		ft_putstr("Colors should contain a comma\n");
	if (is_number(test1) || is_number(test2))
		ft_putstr("Color values should be numeric\n");
	if (is_range(test1) || is_range(test2))
		ft_putstr("Color values should be within range\n");
	return (0);
}

int check_identifier_format(char **identifier)
{
	if (identifier[2] != NULL)
		return 0;
	if (identifier[1][0] == '\n')
		return 0;
	return 1;
}

int check_identifier_extension(t_mx *mlx)
{
	if (ft_strncmp(ft_strrchr(mlx->a, '.'), ".xpm\n", 5) != 0 ||
		ft_strncmp(ft_strrchr(mlx->b, '.'), ".xpm\n", 5) != 0 ||
		ft_strncmp(ft_strrchr(mlx->c, '.'), ".xpm\n", 5) != 0 ||
		ft_strncmp(ft_strrchr(mlx->d, '.'), ".xpm\n", 5) != 0)
	{
		return 0;
	}
	return 1;
}

void parsing_map(t_mx *mlx, char *av)
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
	i = 0;
	while(mlx->height > i)
	{
		if (check_identifier(mlx, i))
			mlx->count++;
		else if (mlx->map[i][j] == '\n')
			k++;
		else
		{
			k = 0;
			if (mlx->count != 6)
				ft_putstr("Errors In Edentifier \n");
			if (mlx->a == NULL || mlx->b == NULL || mlx->c == NULL || mlx->d == NULL || mlx->e == NULL || mlx->f == NULL)
				ft_putstr("Errors In Map \n");
			if (mlx->a[k] == mlx->b[k] == mlx->c[k] == mlx->d[k] == mlx->e[k] == mlx->f[k])
				ft_putstr("Errors In Edentifier \n");
		}
		i++;
	}
	if (check_colors(mlx))
		ft_putstr("Errors in Colors\n");
	char **identifier_a = ft_split(mlx->a, ' ');
	char **identifier_b = ft_split(mlx->b, ' ');
	char **identifier_c = ft_split(mlx->c, ' ');
	char **identifier_d = ft_split(mlx->d, ' ');
	if (!check_identifier_format(identifier_a) || !check_identifier_format(identifier_b) ||
		!check_identifier_format(identifier_c) || !check_identifier_format(identifier_d))
		ft_putstr("Errors in Identifier Format\n");
	if (!check_identifier_extension(mlx))
		ft_putstr("Identifiers do not end with .xpm\n");
	check_walls(mlx);

}
