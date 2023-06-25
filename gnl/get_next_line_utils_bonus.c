/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:49:09 by crepou            #+#    #+#             */
/*   Updated: 2023/01/05 14:52:04 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup(const char *string)
{
	char	*p;
	size_t	len;
	size_t	count;

	len = ft_strlen(string);
	count = 0;
	if (len == 0)
		return (NULL);
	p = (char *)malloc((len * sizeof(char)) + 1);
	if (p)
	{
		while (count < len)
		{
			p[count] = string[count];
			count++;
		}
		p[count] = '\0';
	}
	return (p);
}

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str && str[length])
	{
		length++;
	}
	return (length);
}

static size_t	ft_count(char const *p, size_t len)
{
	size_t	count;

	count = 0;
	while ((*p != '\0') && (count < len))
	{
		count++;
		p++;
	}
	return (count);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t		count;
	char		*sub;
	size_t		i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	count = ft_count(s + start, len);
	sub = (char *)malloc(count + 1);
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*str;
	char	*p;
	char	*s1_ptr;

	if (!s1)
		return (ft_strdup(s2));
	s1_ptr = s1;
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	p = str;
	while (*s1 != '\0')
		*(p++) = *(s1++);
	while (*s2 != '\0')
	{
		*p = *s2;
		p++;
		s2++;
	}
	*p = '\0';
	free(s1_ptr);
	return (str);
}
