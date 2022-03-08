/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <dmedas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:24:47 by dmedas            #+#    #+#             */
/*   Updated: 2021/12/28 16:11:19 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid(t_check *c, int *map, int s)
{
	int	i;

	i = -1;
	while (++i < c->mapx[1])
		if (map[i] != 1)
			return (0);
	i = s;
	while (--i >= s - c->mapx[1])
		if (map[i] != 1)
			return (0);
	i = 0;
	while (i <= s - c->mapx[1])
	{
		if (map[i] != 1)
			return (0);
		i += c->mapx[1];
	}
	i = c->mapx[1] - 1;
	while (i < s)
	{
		if (map[i] != 1)
			return (0);
		i += c->mapx[1];
	}
	return (check_tiles(c));
}

char	*ft_skip_spaces(char *str)
{
	int	i;

	if (*str != ' ')
		return (NULL);
	i = -1;
	while (str[++i] == ' ')
		;
	if (i == 0)
		return (NULL);
	return (str + i);
}

unsigned long	ft_create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void	ft_check_rgb(char **split, t_check *c)
{
	int		i;

	i = 0;
	while (*split != NULL)
	{
		split++;
		i++;
	}
	if (i != 3)
		exit_error(c);
	else if (i == 3)
		return ;
	return ;
}

int	ft_parse_rgb(char *line, t_check *c)
{
	int		rgb[3];
	char	**split;
	int		i;

	split = ft_split(ft_skip_spaces(line), ',');
	ft_check_rgb(split, c);
	i = -1;
	while (++i < 3)
	{
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (-1);
	}
	return ((int)ft_create_rgb(rgb[0], rgb[1], rgb[2]));
}
