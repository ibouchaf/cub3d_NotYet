/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_long_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 09:03:15 by ael-bako          #+#    #+#             */
/*   Updated: 2023/07/15 11:04:01 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_long_line(char **s)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(s[0]);
	while (s[++i])
		if (len < (int)ft_strlen(s[i]))
			len = ft_strlen(s[i]);
	return (len);
}
