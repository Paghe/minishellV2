/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:45:18 by apaghera          #+#    #+#             */
/*   Updated: 2023/07/03 19:49:15 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	count;
	size_t	ret_val;

	count = 0;
	if (!dst && size == 0)
		return (ft_strlen(src));
	if (size < (ft_strlen(dst) + 1))
		ret_val = ft_strlen(src) + size;
	else
		ret_val = ft_strlen(dst) + ft_strlen(src);
	while (*dst != '\0')
	{
		count++;
		dst++;
	}
	while (((count + 1) < size) && (*src != '\0'))
	{
		*dst = *src;
		dst++;
		src++;
		count++;
	}
	*dst = '\0';
	return (ret_val);
}
