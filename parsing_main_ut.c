/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main_ut.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <dmedas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:24:47 by dmedas            #+#    #+#             */
/*   Updated: 2021/12/28 16:11:19 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*realloc_map(int *map, int s, int i)
{
	int	*sav;
	int	j;

	sav = (int *)malloc(sizeof(int) * (s + i));
	j = -1;
	while (++j < s)
		sav[j] = map[j];
	if (s > 0)
		free(map);
	return (sav);
}

void	exit_error(t_check *c)
{
	printf("Error\n");
	free(c->mapx);
	free(c->map);
	close(c->fd);
	exit(0);
}

int	ft_check_options(char **line, t_check *c)
{
	if (ft_strlen(*line) >= 2 && !ft_strncmp(*line, "NO", 2))
		c->north = ft_strdup(ft_skip_spaces(*line + 2));
	else if (ft_strlen(*line) >= 2 && !ft_strncmp(*line, "SO", 2))
		c->south = ft_strdup(ft_skip_spaces(*line + 2));
	else if (ft_strlen(*line) >= 2 && !ft_strncmp(*line, "WE", 2))
		c->west = ft_strdup(ft_skip_spaces(*line + 2));
	else if (ft_strlen(*line) >= 2 && !ft_strncmp(*line, "EA", 2))
		c->east = ft_strdup(ft_skip_spaces(*line + 2));
	else if (ft_strlen(*line) >= 1 && *line[0] == 'F')
		c->floor = ft_parse_rgb(*line + 1, c);
	else if (ft_strlen(*line) >= 1 && *line[0] == 'C')
		c->ceiling = ft_parse_rgb(*line + 1, c);
	else
		return (0);
	if (c->floor < 0 || c->ceiling < 0)
	{
		printf("Error: colors must be between 0 and 255\n");
		exit(1);
	}
	return (1);
}

int	ft_all_spaces(char *line)
{
	int	i;

	if (ft_strlen(line) < 1)
		return (1);
	i = -1;
	while (line[++i] && i < (int)ft_strlen(line) - 1)
		if (*(line++) != ' ')
			return (0);
	return (1);
}

void	parse_map(t_check *c, int *s, char **line, int **map)
{
	if (c->fd < 0)
	{
		printf("Error: file not loaded\n");
		free(c->mapx);
		exit(0);
	}
	s[1] = 0;
	while (get_next_line(c->fd, line))
	{
		if (ft_check_options(line, c))
			;
		else if (ft_all_spaces(*line) && c->f)
			continue ;
		else if (c->f)
			ut(s, line, c);
		if (!c->f && !main_loop(s, line, map, c))
			exit_error(c);
		if (!c->f)
			s[1] += c->mapx[1];
	}
	close(c->fd);
}
