/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:20:25 by ael-bako          #+#    #+#             */
/*   Updated: 2023/07/23 09:05:04 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	res;
	size_t	i;

	if (!dest && size == 0)
		return (ft_strlen(src));
	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size > dest_len)
		res = dest_len + src_len;
	else
		res = src_len + size;
	while (src[i] && (dest_len + 1) < size)
		dest[dest_len++] = src[i++];
	dest[dest_len] = 0;
	return (res);
}
