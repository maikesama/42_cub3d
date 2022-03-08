/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danilo <danilo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:24:47 by dmedas            #+#    #+#             */
/*   Updated: 2022/02/18 19:02:31 by danilo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
}

int	get_pixel(t_img *img, int x, int y)
{
	if (x * y > (img->width - 1) * (img->height - 1) || x < 0 || y < 0)
		return (0x0);
	return (*(int *)(img->addr + (y * img->line_length + (x
				* (img->bits_per_pixel / 8)))));
}

int	ft_find_color(t_img *img, int j, int length, int px)
{
	int	py;
	int	col;

	py = ((float)img->height / (float)length) * (float)j;
	col = get_pixel(img, px, py);
	return (col);
}

//need test
void	data_set(t_data *data, t_check *c, int **s)
{
	data->x = c->p % (*s)[0] * 64 + MAP_OFFSET + 32;
	data->y = c->p / (*s)[0] * 64 + MAP_OFFSET + 32;
	data->mapx = (*s)[0];
	data->mapy = (*s)[1] / (*s)[0];
	data->pa = c->sa;
	data->pdx = cos(data->pa) * DELTA_MOVEMENT;
	data->pdy = sin(data->pa) * DELTA_MOVEMENT;
	data->sangle = 0;
	data->floor = c->floor;
	data->ceiling = c->ceiling;
	data->map = c->map;
	data->w = false;
	data->a = false;
	data->s = false;
	data->d = false;
	data->l = 0.0;
	data->r = 0.0;
	data->prev_x = SW / 2;
	data->mlx = mlx_init();
	ft_load_textures(data, c);
	data->mlx_win = mlx_new_window(data->mlx, SW, SH, "Cub3D");
	mlx_mouse_hide(data->mlx, data->mlx_win);
	mlx_mouse_move(data->mlx, data->mlx_win, 0, SH / 2);
	mlx_hook(data->mlx_win, 2, 1L << 0, ft_set_input, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, ft_unset_input, data);
}
