/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <dmedas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:24:47 by dmedas            #+#    #+#             */
/*   Updated: 2021/12/28 16:11:19 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close_win(void)
{
	exit(0);
	return (0);
}

void	ft_fix_paths(t_check *c)
{
	c->north[ft_strlen(c->north) - 1] = '\0';
	c->south[ft_strlen(c->south) - 1] = '\0';
	c->east[ft_strlen(c->east) - 1] = '\0';
	c->west[ft_strlen(c->west) - 1] = '\0';
}

void	ft_load_textures(t_data *s, t_check *c)
{
	ft_fix_paths(c);
	if (!c->north || !c->south || !c->east || !c->west)
		exit_error(c);
	s->nwall.img = mlx_xpm_file_to_image(s->mlx, c->north,
			&s->nwall.width, &s->nwall.height);
	s->swall.img = mlx_xpm_file_to_image(s->mlx, c->south,
			&s->swall.width, &s->swall.height);
	s->ewall.img = mlx_xpm_file_to_image(s->mlx, c->east,
			&s->ewall.width, &s->ewall.height);
	s->wwall.img = mlx_xpm_file_to_image(s->mlx, c->west,
			&s->wwall.width, &s->wwall.height);
	if (s->nwall.img == NULL || s->swall.img == NULL
		|| s->ewall.img == NULL || s->wwall.img == NULL)
		exit_error(c);
}

int	ft_set_input(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		ft_close_win();
	else if (keycode == KEY_W)
		data->w = true;
	else if (keycode == KEY_A)
		data->a = true;
	else if (keycode == KEY_S)
		data->s = true;
	else if (keycode == KEY_D)
		data->d = true;
	else if (keycode == KEY_LEFT)
		data->l = 0.5;
	else if (keycode == KEY_RIGHT)
		data->r = 0.5;
	ft_close(keycode, data);
	return (keycode);
}

int	ft_unset_input(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->w = false;
	else if (keycode == KEY_A)
		data->a = false;
	else if (keycode == KEY_S)
		data->s = false;
	else if (keycode == KEY_D)
		data->d = false;
	else if (keycode == KEY_LEFT)
		data->l = 0.0;
	else if (keycode == KEY_RIGHT)
		data->r = 0.0;
	return (keycode);
}
