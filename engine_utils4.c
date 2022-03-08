/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <dmedas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:24:47 by dmedas            #+#    #+#             */
/*   Updated: 2021/12/28 16:11:19 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*ft_detect_img(t_data *data, int *j, t_bool dir)
{
	if (j[1] < data->y && dir)
		return (&data->nwall);
	else if (j[1] > data->y && dir)
		return (&data->swall);
	else if (j[0] > data->x && !dir)
		return (&data->ewall);
	else if (j[0] < data->x && !dir)
		return (&data->wwall);
	printf("error: no texture available\n");
	exit(1);
}

double	ft_dist(float *a, float *b)
{
	return (sqrt((b[0] - a[0]) * (b[0] - a[0])
			+ (b[1] - a[1]) * (b[1] - a[1])));
}

void	ft_player(int length, t_data *img, unsigned int col)
{
	int	i;
	int	j;

	i = -length / 2;
	while (i < length / 2)
	{
		j = -length / 2;
		while (j < length / 2)
		{
			my_mlx_pixel_put(img, MINIMAP_RADIUS + i, MINIMAP_RADIUS + j, col);
			j++;
		}
		i++;
	}
}

//Only works if sum is less then 4 * M_PI
float	ft_sum_angle(float a, float b)
{
	if (a + b > 2 * M_PI)
		return (fabs(a - b));
	else if (a + b <= 2 * M_PI)
		return (a + b);
	return (a + b);
}

float	ft_check_sign(float a)
{
	if (a < 0)
		return (-1.0);
	else if (a > 0)
		return (1.0);
	return (0.0);
}
