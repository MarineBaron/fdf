/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 09:23:07 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/08 09:07:27 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include "mlx.h"
# include "mlx_key_macos.h"
# include "libft.h"
# include "fdf_define.h"

typedef unsigned int	t_col;
typedef	struct			s_vertex
{
	double	x;
	double	y;
	double	z;
	double	w;
	t_col	c;
}						t_vertex;
typedef struct			s_vector
{
	t_vertex	*o;
	t_vertex	*d;
}						t_vector;
typedef struct			s_mapi
{
	int			h;
	int			w;
	t_vertex	***vertexes;
}						t_mapi;
typedef	struct			s_world
{
	int		zoom;
	int		rot;
	int		x;
	int		y;
	int		z;
}						t_world;
typedef	struct			s_cam
{
	int		x;
	int		y;
	int		z;
	int		rx;
	int		ry;
	int		rz;
}						t_cam;
typedef	struct			s_proj
{
	int		val;
	int		col;
}						t_proj;
typedef	struct			s_colc
{
	t_col	floor;
	t_col	ceil;
}						t_colc;
typedef struct			s_rect
{
	int		x;
	int		y;
	int		w;
	int		h;
	t_col	c_bg;
	t_col	c_bd;
}						t_rect;
typedef struct			s_param
{
	char		*name;
	int			*value;
	int			min;
	int			max;
	int			kdwn;
	int			kup;
	t_rect		*pos_param;
	t_rect		*pos_value;
	t_rect		**buttons;
}						t_param;
typedef struct			s_control
{
	char		*title;
	int			p_nb;
	t_param		**params;
	t_rect		*pos_title;
}						t_control;
typedef struct			s_map
{
	t_rect		*rect;
	t_vector	**vectors;
}						t_map;
typedef struct			s_conf
{
	t_world		*world;
	t_cam		*camera;
	t_proj		*proj;
	t_colc		*color;
	t_mapi		*mapi;
	t_control	*control[3];
	t_map		*map;
	void		*mlx;
	void		*win;
	void		*img;
	char		*ptr;
	int			bpp;
	int			sl;
	int			end;
}						t_conf;
t_conf					*config_init(int argc, char *argv[]);
void					config_control_set_world(t_conf *conf);
void					config_control_set_camera(t_conf *conf);
void					config_control_set_proj(t_conf *conf);
void					config_control_set_pos(t_conf *conf);
void					config_control_init_pos(t_rect *rect, t_rect *button);
void					config_control_set_param(t_param *param,
	const char *name, int *p_value);
void					config_control_set_minmax(t_param *param, int min,
	int max);
void					config_control_set_keys(t_param *param, int kup,
	int kdwn);
void					set_img_control(t_conf *conf);
void					set_img_control_value(t_conf *conf);
void					set_txt_control(t_conf *conf);
void					set_txt_control_value(t_conf *conf);
void					set_img_clear(t_conf *conf);
void					set_img_map(t_conf *conf);
void					render(t_conf *conf);
int						hook_key(int key, t_conf *conf);
int						hook_mouse(int button, int x, int y, t_conf *conf);

unsigned int			ft_atoi_hex(char *str);
int						set_error(char *str, int exit);
void					*init_pointer(size_t size, char *str_error);
void					fill_rect(t_conf *conf, t_rect *rect);
#endif
