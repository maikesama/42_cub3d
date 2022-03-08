/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <dmedas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:24:47 by dmedas            #+#    #+#             */
/*   Updated: 2021/12/28 16:11:19 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move(t_data *vars)
{
	if (vars->a && ft_collision_check(vars, -vars->pdy, -vars->pdx))
	{
		vars->x -= vars->pdy;
		vars->y -= vars->pdx;
	}
	else if (vars->d && ft_collision_check(vars, vars->pdy, vars->pdx))
	{
		vars->x += vars->pdy;
		vars->y += vars->pdx;
	}
	else if (vars->w && ft_collision_check(vars, vars->pdx, -vars->pdy))
	{
		vars->x += vars->pdx;
		vars->y -= vars->pdy;
	}
	else if (vars->s && ft_collision_check(vars, -vars->pdx, vars->pdy))
	{
		vars->x -= vars->pdx;
		vars->y += vars->pdy;
	}
}

void	input(t_data *vars)
{
	ft_turn(vars);
	ft_move(vars);
	return ;
}

void	ft_border_check(t_data *data, int *mouse_x, int mouse_y)
{
	if (*mouse_x > SW)
	{
		data->sangle += SW;
		if (data->sangle >= SW * (360 / MOUSE_SENS))
			data->sangle -= SW * (360 / MOUSE_SENS);
		mlx_mouse_move(data->mlx, data->mlx_win, 0, mouse_y);
		*mouse_x = 0;
	}
	if (*mouse_x < 0)
	{
		data->sangle -= SW;
		if (data->sangle < 0)
			data->sangle += SW * (360 / MOUSE_SENS);
		mlx_mouse_move(data->mlx, data->mlx_win, SW, mouse_y);
		*mouse_x = SW;
	}
	if (mouse_y > SH)
		mlx_mouse_move(data->mlx, data->mlx_win, *mouse_x, SH / 2);
	if (mouse_y < 0)
		mlx_mouse_move(data->mlx, data->mlx_win, *mouse_x, SH / 2);
}

void	ft_check_mouse(t_data *data)
{
	int	mouse_x;
	int	mouse_y;

	mlx_mouse_get_pos(data->mlx, data->mlx_win, &mouse_x, &mouse_y);
	ft_border_check(data, &mouse_x, mouse_y);
	data->pa = (float)(data->sangle + mouse_x)
		/ (float)(SW * (360 / MOUSE_SENS)) *(2.0 * M_PI);
	data->pdx = cos(-data->pa) * DELTA_MOVEMENT;
	data->pdy = sin(-data->pa) * DELTA_MOVEMENT;
}

int	ft_render_next_frame(t_data *s)
{
	s->img = mlx_new_image(s->mlx, SW, SH);
	s->addr = mlx_get_data_addr(s->img, &s->bits_per_pixel, &s->line_length,
			&s->endian);
	s->nwall.addr = mlx_get_data_addr(s->nwall.img, &s->nwall.bits_per_pixel,
			&s->nwall.line_length, &s->nwall.endian);
	s->swall.addr = mlx_get_data_addr(s->swall.img, &s->swall.bits_per_pixel,
			&s->swall.line_length, &s->swall.endian);
	s->ewall.addr = mlx_get_data_addr(s->ewall.img, &s->ewall.bits_per_pixel,
			&s->ewall.line_length, &s->ewall.endian);
	s->wwall.addr = mlx_get_data_addr(s->wwall.img, &s->wwall.bits_per_pixel,
			&s->wwall.line_length, &s->wwall.endian);
	mlx_mouse_hide(s->mlx, s->mlx_win);
	input(s);
	ft_check_mouse(s);
	ft_cast_ray(s);
	ft_draw_map(s);
	ft_player(5, s, 0xff0000);
	mlx_put_image_to_window(s->mlx, s->mlx_win, s->img, 0, 0);
	mlx_destroy_image(s->mlx, s->img);
	return (0);
}
