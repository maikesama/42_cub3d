/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danilo <danilo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:57:13 by dmedas            #+#    #+#             */
/*   Updated: 2022/02/18 19:10:20 by danilo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef __APPLE__
#  include "mlx/mlx.h"
#  define mlx_mouse_get_pos(M, W, X, Y) mlx_mouse_get_pos(W, X, Y)
#  define mlx_mouse_move(M, W, X, Y) mlx_mouse_move(W, X, Y)
#  define mlx_mouse_hide(M, W) mlx_mouse_hide()
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# elif __linux__
#  include "minilibx-linux/mlx.h"
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
# endif

# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>//eliminare

# define PI2 M_PI / 2.0
# define PI3 3.0 * M_PI / 2.0
# define MAP_OFFSET 384
# define DR 0.0174533
# define DOF 40 //default = 40 [da risolvere, se si abbassa questo valore, il programma esplode]
# define SW 720 //default = 1920
# define SH (int)((double)SW * (double)0.5625) //default = 1080
# define DELTA_MOVEMENT (double)SW / 307.2 //default = 384.0
# define FOV 75.0
# define MOUSE_SENS FOV * 0.7
# define TILE (int)64
# define BUFFER_SIZE 1
# define MAX_FD 1024 + 1
# define RET_VALUE(ret)	ret > 0 ? 1 : ret
# define MINI_MAP_C 256
# define MINIMAP_RADIUS (double)SW / 9.6 // default = 200.0

typedef enum e_bool{
	false,
	true
}			t_bool;

typedef struct s_img{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_data{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx;
	void		*mlx_win;
	int			*map;
	int			*mx;
	float		pa;
	int			x;
	int			y;
	int			mapx;
	int			mapy;
	float		pdx;
	float		pdy;
	int			sangle;
	t_img		nwall;
	t_img		swall;
	t_img		ewall;
	t_img		wwall;
	int			floor;
	int			ceiling;
	t_bool		w;
	t_bool		a;
	t_bool		s;
	t_bool		d;
	float		l;
	float		r;
	int			prev_x;
}				t_data;

typedef struct s_rcast{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	int		j[3];
	int		distt;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	ncotan;
	float	ntan;
	float	i[2];
	float	h[2];
	float	v[2];
	float	lineh;
	float	ca;
	double	dish;
	double	disv;
	t_bool	dir;
}				t_rcast;

typedef struct s_check{
	int		walls;
	int		start;
	int		empty;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		floor;
	int		ceiling;
	int		*mapx;
	int		fd;
	int		*map;
	float	sa;
	int		f;
	int		p;
}				t_check;

typedef struct s_buff{
	char			buf[BUFFER_SIZE + 1];
	int				fd;
	struct s_buff	*next;
}				t_buff;

typedef struct s_ut
{
	int		i;
	int		j;
	float	xdiff;
	float	ydiff;
	float	dist;
}				t_ut;

typedef struct s_vl
{
	int		i;
	int		j[3];
	int		ax;
	int		yy;
	int		length;
}				t_vl;

//parsing
int				get_next_line(int fd, char **line);
void			ft_shift_buf(char *b, int i);
size_t			ft_strlen(const char *s);
char			*ft_realloc_res(char *comp, long long b_size, long long sz);
int				ft_init_buff(t_buff *b, int fd);
int				main_loop(int *s, char **line,
					int **map, t_check *c);
void			init_check(t_check *c, char *fn);
int				check_tiles(t_check *c);
int				*realloc_map(int *map, int s, int i);
int				is_valid(t_check *c, int *map, int s);
void			exit_error(t_check *c);
void			parse_map(t_check *c, int *s, char **line, int **map);

//Raycaster engine
void			ft_square(int *pos, int length, t_data *img, unsigned int col);
void			ft_border_check(t_data *data, int *mouse_x, int mouse_y);
void			ft_turn(t_data *vars);

//utils.c
int				ft_strncmp(char *s1, char *s2, unsigned int n);
char			**ft_split(char const *s, char c);
char			*ft_strdup(char *src);
int				ft_atoi(const char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
void			ut(int *s, char **line, t_check *c);

//norm_utils
int				ft_unset_input(int keycode, t_data *data);
int				ft_set_input(int keycode, t_data *data);
void			ft_load_textures(t_data *s, t_check *c);
void			ft_fix_paths(t_check *c);
int				ft_close_win(void);
int				ft_render_next_frame(t_data *s);
void			ft_check_mouse(t_data *data);
void			ft_border_check(t_data *data, int *mouse_x, int mouse_y);
void			input(t_data *vars);
void			ft_move(t_data *vars);
t_bool			ft_collision_check(t_data *s, int xadd, int yadd);
void			ft_turn(t_data *vars);
void			ft_close(int keycode, t_data *vars);
void			ft_draw_map(t_data *img);
float			ft_fix_angle(float a);
t_img			*ft_detect_img(t_data *data, int *j, t_bool dir);
double			ft_dist(float *a, float *b);
void			ft_player(int length, t_data *img, unsigned int col);
float			ft_sum_angle(float a, float b);
void			data_set(t_data *data, t_check *c, int **s);
int				ft_find_color(t_img *img, int j, int length, int px);
int				get_pixel(t_img *img, int x, int y);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			ft_square(int *pos, int length, t_data *img, unsigned int col);
char			*ft_skip_spaces(char *str);
int				ft_parse_rgb(char *line, t_check *c);
float			ft_check_sign(float a);
void			ft_cast_ray(t_data *img);

#endif