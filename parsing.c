/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <dmedas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:24:47 by dmedas            #+#    #+#             */
/*   Updated: 2021/12/28 16:11:19 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	inner_loop_2(char **line, int *s, int **map, t_check *c)
{
	if (line[0][*s] == 'S')
	{
		map[0][s[1] + *s] = 0;
		c->p = s[1] + *s;
		c->sa = PI2;
		c->start++;
	}
	else if (line[0][*s] == 'E')
	{
		map[0][s[1] + *s] = 0;
		c->p = s[1] + *s;
		c->sa = 0;
		c->start++;
	}
	else if (line[0][*s] == 'W')
	{
		map[0][s[1] + *s] = 0;
		c->p = s[1] + *s;
		c->sa = M_PI;
		c->start++;
	}
	return ;
}

static void	inner_loop(char **line, int *s, int **map, t_check *c)
{
	if (line[0][*s] == '0')
	{
		map[0][s[1] + *s] = 0;
		c->empty++;
	}
	else if (line[0][*s] == '1' || line[0][*s] == ' ')
	{
		map[0][s[1] + *s] = 1;
		c->walls++;
	}
	else if (line[0][*s] == 'N')
	{
		map[0][s[1] + *s] = 0;
		c->p = s[1] + *s;
		c->sa = PI3;
		c->start++;
	}
	else
		inner_loop_2(line, s, map, c);
	return ;
}

int	main_loop(int *s, char **line,
	int **map, t_check *c)
{
	*s = -1;
	while (line[0][++s[0]])
		;
	if (line[0][s[0] - 1] == '1' || line[0][s[0] - 1] == ' ')
		s[0]++;
	c->mapx[1] = s[0] - 1;
	*map = realloc_map(*map, s[1], c->mapx[1]);
	*s = -1;
	while (line[0][++s[0]])
		inner_loop(line, s, map, c);
	if (line[0][s[0] - 1] != '1' && line[0][s[0] - 1] != ' ')
		s[0]--;
	free(*line);
	if (c->mapx[0] != c->mapx[1])
		return (0);
	c->mapx[0] = c->mapx[1];
	return (1);
}

void	init_check(t_check *c, char *fn)
{
	c->empty = 0;
	c->start = 0;
	c->walls = 0;
	c->sa = 0;
	c->mapx = (int *)malloc(sizeof(int) * 2);
	c->fd = open(fn, O_RDONLY);
	c->f = 1;
}

int	check_tiles(t_check *c)
{
	if (c->empty <= 0)
		return (0);
	if (c->start != 1)
		return (0);
	if (c->walls <= 0)
		return (0);
	return (1);
}
