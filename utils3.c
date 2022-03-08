/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <dmedas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:24:47 by dmedas            #+#    #+#             */
/*   Updated: 2021/12/28 16:11:19 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ut(int *s, char **line, t_check *c)
{
	*s = -1;
	while (line[0][++s[0]])
		;
	c->mapx[0] = s[0] - 1;
	c->f = 0;
}

void	ut_square_two(t_ut *ut, t_data *img)
{
	if (ut->xdiff == 0.0 && ut->ydiff != 0.0)
	{
		ut->xdiff = -cos(acos(fabs(ut->xdiff) / ut->dist) + img->pa + PI2)
			* ut->dist * ft_check_sign(ut->ydiff);
		ut->ydiff = sin(asin(fabs(ut->ydiff) / ut->dist) + img->pa + PI2)
			* ut->dist * ft_check_sign(ut->ydiff);
	}
	else if (ut->xdiff != 0.0 && ut->ydiff == 0.0)
	{
		ut->xdiff = cos(acos(fabs(ut->xdiff) / ut->dist) + img->pa + PI2)
			* ut->dist * ft_check_sign(ut->xdiff);
		ut->ydiff = -sin(asin(fabs(ut->ydiff) / ut->dist)
				+ ft_fix_angle(img->pa) + PI2)
			* ut->dist * ft_check_sign(ut->xdiff);
	}
}

void	ut_square(int *pos, t_ut *ut, t_data *img)
{
	ut->xdiff = (pos[0] + ut->i) - (4 * TILE + MAP_OFFSET);
	ut->ydiff = (pos[1] + ut->j) - (4 * TILE + MAP_OFFSET);
	ut->dist = sqrt(pow(ut->xdiff, 2) + pow(ut->ydiff, 2));
	if (ut->xdiff * ut->ydiff < 0)
	{
		ut->xdiff = cos(acos(fabs(ut->xdiff) / ut->dist) + img->pa + PI2)
			* ut->dist * ft_check_sign(ut->xdiff);
		ut->ydiff = sin(asin(fabs(ut->ydiff) / ut->dist) + img->pa + PI2)
			* ut->dist * ft_check_sign(ut->ydiff);
	}
	else if (ut->xdiff * ut->ydiff > 0)
	{
		ut->xdiff = cos(acos(fabs(ut->xdiff) / ut->dist) - img->pa - PI2)
			* ut->dist * ft_check_sign(ut->xdiff);
		ut->ydiff = sin(asin(fabs(ut->ydiff) / ut->dist) - img->pa - PI2)
			* ut->dist * ft_check_sign(ut->ydiff);
	}
	else if (ut->xdiff * ut->ydiff == 0.0)
		ut_square_two(ut, img);
}

void	ft_square(int *pos, int length, t_data *img, unsigned int col)
{
	t_ut	ut;

	ut.i = 0;
	while (ut.i < length)
	{
		ut.j = 0;
		while (ut.j < length)
		{
			ut_square(pos, &ut, img);
			ut.j++;
			if (sqrt(pow(ut.xdiff, 2) + pow(ut.ydiff, 2)) <= MINIMAP_RADIUS)
				my_mlx_pixel_put(img, ut.xdiff + MINIMAP_RADIUS,
					ut.ydiff + MINIMAP_RADIUS, col);
		}
		ut.i++;
	}
}
