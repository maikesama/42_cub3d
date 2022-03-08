/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danilo <danilo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:24:47 by dmedas            #+#    #+#             */
/*   Updated: 2022/02/18 18:54:15 by danilo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_bzero(void *b, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	dest = b;
	i = 0;
	while (i++ < n)
		*dest++ = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size * count);
	return (ptr);
}

int	ft_count_rows(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (i + 1);
}

int	check(char **matrix, int p)
{
	if (!matrix[p])
	{
		while (p)
		{
			p--;
			free(matrix[p]);
		}
		free(matrix);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char			**res;
	char			*start;
	unsigned int	i;
	unsigned int	len;

	res = (char **)ft_calloc(ft_count_rows(s, c), sizeof(char *));
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = (char *)s;
			while (*s && *s != c)
				s++;
			len = s - start + 1;
			res[i] = (char *)malloc(len);
			if (!(check(res, i)))
				return (0);
			ft_strlcpy(res[i++], start, len);
		}
		else
			s++;
	}
	return (res);
}
