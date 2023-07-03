/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:12:47 by apaghera          #+#    #+#             */
/*   Updated: 2022/11/03 13:11:54 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*p;

	if (!str)
		return (NULL);
	p = (char *)str;
	while (str++)
	{
		if (*p == (char )c)
			return (p);
		if (!*p)
			return (0);
		p++;
	}
	if (*p == (char)c)
		return (p);
	return (0);
}
