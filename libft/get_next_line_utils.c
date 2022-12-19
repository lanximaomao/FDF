/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:39:34 by lsun              #+#    #+#             */
/*   Updated: 2022/12/19 19:44:35 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//size_t	ft_strlen(const char *str)
//{
//	size_t	len;

//	len = 0;
//	while (str[len] != '\0')
//		len++;
//	return (len);
//}

size_t	ft_strlen_nl(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		return (len + 1);
	return (0);
}

//char	*ft_strchr(const char *s, int c)
//{
//	int		i;
//	char	a;

//	i = 0;
//	a = (char)c;
//	if (!s)
//		return (0);
//	while (*s)
//	{
//		if (*s == a)
//			return ((char *)s);
//		s++;
//	}
//	if (*s == a)
//		return ((char *)s);
//	return (0);
//}

//char	*ft_strdup(const char *src)
//{
//	int		i;
//	int		len;
//	char	*dest;

//	i = 0;
//	len = ft_strlen((char *)src);
//	if (!src && !*src)
//		return (NULL);
//	dest = (char *)ft_calloc((len + 1), sizeof(*src));
//	if (!dest)
//		return (NULL);
//	while (src[i] != '\0')
//	{
//		dest[i] = src[i];
//		i++;
//	}
//	dest[i] = '\0';
//	return (dest);
//}

//void	*ft_calloc(size_t count, size_t size)
//{
//	size_t	i;
//	char	*start;

//	i = 0;
//	if (count == 0 || size == 0)
//		return (ft_calloc(1, 1));
//	if (count * size / size != count)
//		return (NULL);
//	start = (char *)malloc(size * count);
//	if (!start)
//		return (NULL);
//	while (i < size * count)
//	{
//		start[i] = '\0';
//		i++;
//	}
//	return ((void *)start);
//}
