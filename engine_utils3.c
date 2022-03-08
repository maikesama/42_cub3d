/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <dmedas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:24:47 by dmedas            #+#    #+#             */
/*   Updated: 2021/12/28 16:11:19 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_fix_angle(float a)
{
	if (a <= M_PI)
		a += M_PI;
	return (a);
}

void	ft_draw_map(t_data *img)
{
	int	i;
	int	j;
	int	pos[2];

	i = (img->x - MAP_OFFSET) / TILE - 4;
	while (i < img->mapx && i < (img->x - MAP_OFFSET) / TILE + 4)
	{
		j = (img->y - MAP_OFFSET) / TILE - 4;
		while (j < img->mapy && j < (img->y - MAP_OFFSET) / TILE + 4)
		{
			pos[0] = (i - (img->x - MAP_OFFSET) / TILE + 4)
				* TILE + MAP_OFFSET - img->x % TILE;
			pos[1] = (j - (img->y - MAP_OFFSET) / TILE + 4)
				* TILE + MAP_OFFSET - img->y % TILE;
			if (i < img->mapx && j < img->mapy)
				if (i >= 0 && j >= 0 && img->map[j * img->mapx + i] == 1)
					ft_square(pos, 64, img, 0xff);
			j++;
		}
		i++;
	}
}

void	ft_close(int keycode, t_data *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit(0);
	}
}

void	ft_turn(t_data *vars)
{
	int	mouse_x;
	int	mouse_y;

	mlx_mouse_get_pos(vars->mlx, vars->mlx_win, &mouse_x, &mouse_y);
	if (vars->l > 0)
	{
		vars->pa -= 0.098175 * vars->l;
		if (vars->pa <= 0)
			vars->pa += (2 * M_PI);
		mlx_mouse_move(vars->mlx, vars->mlx_win, mouse_x
			- (int)((0.098175 * vars->l / 2.0 * M_PI) * (float)SW), mouse_y);
		vars->pdx = cos(-vars->pa) * DELTA_MOVEMENT;
		vars->pdy = sin(-vars->pa) * DELTA_MOVEMENT;
	}
	if (vars->r > 0)
	{
		vars->pa += 0.098175 * vars->r;
		if (vars->pa >= 2 * M_PI)
			vars->pa -= 2 * M_PI;
		mlx_mouse_move(vars->mlx, vars->mlx_win, mouse_x
			+ (int)((0.098175 * vars->r / 2.0 * M_PI) * (float)SW), mouse_y);
		vars->pdx = cos(-vars->pa) * DELTA_MOVEMENT;
		vars->pdy = sin(-vars->pa) * DELTA_MOVEMENT;
	}
}

t_bool	ft_collision_check(t_data *s, int xadd, int yadd)
{
	int	xx;
	int	yy;

	xx = (s->x - MAP_OFFSET + xadd) / 64;
	yy = (s->y - MAP_OFFSET + yadd) / 64;
	if (s->map[yy * s->mapx + xx] == 1)
		return (false);
	return (true);
}
