/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danilo <danilo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:57:06 by dmedas            #+#    #+#             */
/*   Updated: 2022/02/18 19:06:04 by danilo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//moltiplicatore sotto detect img da modificare in base alla texture
void	ft_draw_vline_ut(t_data *img, t_img **wall, t_vl *vl, t_bool dir)
{
	vl->yy = (SH - vl->length) / 2;
	*wall = ft_detect_img(img, vl->j, dir);
	vl->ax = (vl->j[!dir] / 3) % (*wall)->width + 1;
	vl->i = 0;
	while (vl->i <= vl->length / 2 && vl->yy <= SH / 2)
	{
		if (vl->yy > 0)
			my_mlx_pixel_put(img, vl->j[2], vl->yy,
				ft_find_color(*wall, (vl->length / 2) - vl->i, vl->length,
					vl->ax));
		vl->yy++;
		vl->i++;
	}
	vl->yy = SH / 2;
	vl->i = 0;
}

void	ft_draw_vline(int length, t_data *img, int *j, t_bool dir)
{
	t_vl	vl;
	t_img	*wall;

	wall = NULL;
	vl.length = length;
	vl.j[0] = j[0];
	vl.j[1] = j[1];
	vl.j[2] = j[2];
	ft_draw_vline_ut(img, &wall, &vl, dir);
	while (vl.i < length / 2 && vl.yy < SH)
	{
		my_mlx_pixel_put(img, j[2], vl.yy,
			ft_find_color(wall, (length / 2) + vl.i, length, vl.ax));
		vl.yy++;
		vl.i++;
	}
	vl.i = (SH / 2) + (length / 2) - 1;
	while (++vl.i < SH)
		my_mlx_pixel_put(img, j[2], vl.i, img->floor);
	vl.i = (SH / 2) - (length / 2) + 1;
	while (--vl.i > 0)
		my_mlx_pixel_put(img, j[2], vl.i, img->ceiling);
}

void	ft_vdof_loop(t_rcast *raycast, t_data *img)
{
	raycast->mx = (int)(raycast->rx - (float)MAP_OFFSET) >> 6;
	raycast->my = (int)(raycast->ry - (float)MAP_OFFSET) >> 6;
	raycast->mp = raycast->my * img->mapx + raycast->mx;
	if (raycast->mp >= 0 && raycast->mp < img->mapx * img->mapy
		&& img->map[raycast->mp] == 1)
	{
		raycast->h[0] = raycast->rx;
		raycast->h[1] = raycast->ry;
		raycast->dish = ft_dist(raycast->i, raycast->h);
		raycast->dof = DOF;
	}
	else
	{
		raycast->rx += raycast->xo;
		raycast->ry += raycast->yo;
		raycast->dof += 1;
	}
}

void	ft_hdof_loop(t_rcast *raycast, t_data *img)
{
	raycast->v[0] = raycast->rx;
	raycast->v[1] = raycast->ry;
	raycast->rx -= 0.0000009 * ft_dist(raycast->i, raycast->v);
	raycast->mx = (int)(raycast->rx - (float)MAP_OFFSET) >> 6;
	raycast->my = (int)(raycast->ry - (float)MAP_OFFSET) >> 6;
	raycast->mp = raycast->my * img->mapx + raycast->mx;
	if (raycast->mp >= 0 && raycast->mp < img->mapx * img->mapy
		&& img->map[raycast->mp] == 1)
	{
		raycast->v[0] = raycast->rx;
		raycast->v[1] = raycast->ry;
		raycast->disv = ft_dist(raycast->i, raycast->v);
		raycast->dof = DOF;
	}
	else
	{
		raycast->rx += raycast->xo;
		raycast->ry += raycast->yo;
		raycast->dof += 1;
	}
}

void	ft_vangle_check(t_rcast *raycast, t_data *img)
{
	if (raycast->ra > M_PI)
	{
		raycast->ry = (float)((img->y >> 6) << 6)
			- 0.0001;
		raycast->rx = ((float)img->y - raycast->ry) * raycast->ncotan
			+ (float)img->x;
		raycast->yo = -64;
		raycast->xo = (float)-raycast->yo * raycast->ncotan;
	}
	if (raycast->ra < M_PI)
	{
		raycast->ry = (float)((img->y >> 6) << 6)
			+ 64.0f;
		raycast->rx = ((float)img->y - raycast->ry) * raycast->ncotan
			+ (float)img->x;
		raycast->yo = 64;
		raycast->xo = (float)-raycast->yo * raycast->ncotan;
	}
	if (raycast->ra == 0 || raycast->ra == M_PI)
	{
		raycast->rx = img->x;
		raycast->ry = img->y;
		raycast->dof = DOF;
	}
}

void	ft_hangle_check(t_rcast *raycast, t_data *img)
{
	if (raycast->ra > PI2 && raycast->ra < PI3)
	{
		raycast->rx = (float)((img->x >> 6) << 6)
			- 0.0001;
		raycast->ry = ((float)img->x - raycast->rx) * raycast->ntan
			+ (float)img->y;
		raycast->xo = -64;
		raycast->yo = (float)-raycast->xo * raycast->ntan;
	}
	if (raycast->ra < PI2 || raycast->ra > PI3)
	{
		raycast->rx = (float)((img->x >> 6) << 6)
			+ 64.1f;
		raycast->ry = ((float)img->x - raycast->rx) * raycast->ntan
			+ (float)img->y;
		raycast->xo = 64;
		raycast->yo = (float)-raycast->xo * raycast->ntan;
	}
	if (raycast->ra == PI2 || raycast->ra == PI3)
	{
		raycast->rx = img->x;
		raycast->ry = img->y;
		raycast->dof = DOF;
	}
}

void	ft_shortest_ray(t_rcast *raycast, t_data *img)
{
	if (raycast->dish < raycast->disv)
	{
		raycast->rx = raycast->h[0];
		raycast->ry = raycast->h[1];
		raycast->distt = raycast->dish;
		raycast->dir = true;
	}
	else if (raycast->disv <= raycast->dish)
	{
		raycast->rx = raycast->v[0];
		raycast->ry = raycast->v[1];
		raycast->distt = raycast->disv;
		raycast->dir = false;
	}
	raycast->j[0] = (int)raycast->rx;
	raycast->j[1] = (int)raycast->ry;
	raycast->ca = img->pa - raycast->ra;
}

void	ft_rc_draw(t_rcast *raycast, t_data *img)
{
	if (raycast->ca < 0)
		raycast->ca += 2 * M_PI;
	if (raycast->ca > 2 * M_PI)
		raycast->ca -= 2 * M_PI;
	raycast->distt = raycast->distt * cos(raycast->ca);
	if (raycast->distt == 0)
		raycast->distt = 5;
	raycast->lineh = (TILE * SH) / raycast->distt;
	ft_draw_vline(raycast->lineh, img, raycast->j, raycast->dir);
	raycast->j[2] += 1;
	raycast->r++;
	raycast->ra += ((double)FOV * (double)DR) / (double)SW;
	if (raycast->ra < 0)
		raycast->ra += 2 * M_PI;
	if (raycast->ra > 2 * M_PI)
		raycast->ra -= 2 * M_PI;
}

void	ft_rc_main_loop(t_rcast *raycast, t_data *img)
{
	raycast->dof = 0;
	raycast->dish = 1000000.0;
	raycast->h[0] = img->x;
	raycast->h[1] = img->y;
	if (raycast->ra != 0)
		raycast->ncotan = -1.0 / tan(raycast->ra);
	else if (raycast->ra == 0)
		raycast->ncotan = -1.0 / 0.1;
	ft_vangle_check(raycast, img);
	while (raycast->dof < DOF)
		ft_vdof_loop(raycast, img);
	raycast->dof = 0;
	raycast->disv = 1000000;
	raycast->v[0] = img->x;
	raycast->v[1] = img->y;
	raycast->ntan = -tan(raycast->ra);
	ft_hangle_check(raycast, img);
	while (raycast->dof < DOF)
		ft_hdof_loop(raycast, img);
	ft_shortest_ray(raycast, img);
	ft_rc_draw(raycast, img);
}

void	ft_cast_ray(t_data *img)
{
	t_rcast	raycast;

	raycast.j[2] = 0;
	raycast.ra = img->pa - DR * (FOV / 2);
	if (raycast.ra < 0)
		raycast.ra += 2 * M_PI;
	if (raycast.ra > 2 * M_PI)
		raycast.ra -= 2 * M_PI;
	raycast.r = 0;
	raycast.i[0] = (float)img->x;
	raycast.i[1] = (float)img->y;
	while (raycast.r < SW)
		ft_rc_main_loop(&raycast, img);
}

int	main(int argc, char **argv)
{
	char	*line;
	int		s[2];
	int		*sp;
	t_data	data;
	t_check	c;

	if (argc != 2)
	{
		printf("Error: wrong number of arguments\n");
		exit(0);
	}
	sp = s;
	init_check(&c, argv[1]);
	c.floor = 0;
	c.ceiling = 0;
	parse_map(&c, s, &line, &c.map);
	if (!is_valid(&c, c.map, s[1]))
		exit_error(&c);
	data_set(&data, &c, &sp);
	mlx_loop_hook(data.mlx, ft_render_next_frame, &data);
	mlx_loop(data.mlx);
	return (1);
}
