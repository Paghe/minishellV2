/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:37:01 by apaghera          #+#    #+#             */
/*   Updated: 2022/11/03 13:17:19 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s2;
	char	find;
	int		i;

	s2 = (char *)s;
	find = (char) c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (s2[i] == find)
			return (s2 + i);
		i--;
	}
	if (s2[i] == find)
		return (s2);
	return (0);
}
