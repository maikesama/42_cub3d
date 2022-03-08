/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danilo <danilo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:24:33 by dmedas            #+#    #+#             */
/*   Updated: 2022/02/18 16:15:48 by danilo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != 0)
		l++;
	return (l);
}

void	ft_shift_buf(char *b, int i)
{
	int	j;

	j = 0;
	while (b[i])
	{
		b[j] = b[i];
		i++;
		j++;
	}
	b[j] = '\0';
}

char	*ft_realloc_res(char *comp, long long b_size, long long sz)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = (char *)malloc(sizeof(char) * (sz + b_size));
	while (comp[++i])
		tmp[i] = comp[i];
	tmp[i] = '\0';
	free(comp);
	return (tmp);
}

int	ft_init_buff(t_buff *b, int fd)
{
	int	i;

	i = -1;
	while (++i < 1000)
	{
		if (b[i].fd == fd)
			break ;
		if (b[i].fd == -1)
		{
			b[i].buf[0] = '\0';
			b[i].fd = fd;
			if (i < 1000)
				b[i + 1].fd = -1;
			break ;
		}
	}
	return (i);
}
