/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 09:23:07 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/06 15:23:12 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include "mlx.h"
# include "libft.h"
# define FDF_WIN_W 1500
# define FDF_WIN_H 800
# define FDF_MARGE 10
# define FDF_CONTROL_W 400
# define FDF_CONTROL_X FDF_MARGE
# define FDF_CONTROL_Y FDF_MARGE
# define FDF_MAP_W FDF_WIN_W - FDF_CONTROL_W - 3 * FDF_MARGE
# define FDF_MAP_H FDF_WIN_H - 2 * FDF_MARGE
# define FDF_MAP_X FDF_CONTROL_W + 2 * FDF_MARGE
# define FDF_MAP_Y FDF_MARGE
# define FDF_CONTROL_MARGE 2
# define FDF_CONTROL_H 25
# define FDF_CONTROL_C_H FDF_CONTROL_H - 2 * FDF_CONTROL_MARGE
# define FDF_CONTROL_C_W FDF_CONTROL_C_H
# define FDF_CONTROL_P_X FDF_MARGE + 2 * FDF_CONTROL_MARGE
# define FDF_CONTROL_C2_X FDF_MARGE + FDF_CONTROL_W - FDF_CONTROL_C_W - FDF_CONTROL_MARGE
# define FDF_CONTROL_C1_X FDF_CONTROL_C2_X - FDF_CONTROL_MARGE - FDF_CONTROL_C_W
# define FDF_CONTROL_V_X FDF_CONTROL_C1_X - FDF_CONTROL_MARGE - 2 * FDF_CONTROL_C_W
# define FDF_CONTROL_C_DEC 5
# define FDF_MAP_BG_COLOR 0x202020
# define FDF_MAP_BD_COLOR 0x202020
# define FDF_CONTROL_BG_COLOR 0x202020
# define FDF_CONTROL_BD_COLOR 0x303030
# define FDF_CONTROL_BUTTON1_COLOR 0x404040
# define FDF_CONTROL_BUTTON2_COLOR 0x505050
# define FDF_CONTROL_TXT1_COLOR 0xA0A0A0
# define FDF_CONTROL_TXT2_COLOR 0xC0C0C0
# define FDF_PARAM_NB_WORLD 5
# define FDF_PARAM_NB_CAMERA 6
# define FDF_PARAM_NB_PROJ 4
# define FDF_MIN_WORLD_X 0
# define FDF_MAX_WORLD_X 100
# define FDF_MIN_WORLD_Y 0
# define FDF_MAX_WORLD_Y 100
# define FDF_MIN_WORLD_Z 0
# define FDF_MAX_WORLD_Z 100
# define FDF_MIN_WORLD_ZOOM 0
# define FDF_MAX_WORLD_ZOOM 100
# define FDF_MIN_WORLD_ROT 0
# define FDF_MAX_WORLD_ROT 360
# define FDF_MIN_CAM_X -100
# define FDF_MAX_CAM_X 100
# define FDF_MIN_CAM_Y -100
# define FDF_MAX_CAM_Y 100
# define FDF_MIN_CAM_Z -100
# define FDF_MAX_CAM_Z 100
# define FDF_MIN_CAM_RX 0
# define FDF_MAX_CAM_RX 360
# define FDF_MIN_CAM_RY 0
# define FDF_MAX_CAM_RY 360
# define FDF_MIN_CAM_RZ 0
# define FDF_MAX_CAM_RZ 360
# define FDF_MIN_PROJ_VAL 1
# define FDF_MAX_PROJ_VAL 4
# define FDF_MIN_PROJ_COL 0
# define FDF_MAX_PROJ_COL 2
# define FDF_MIN_PROJ_COLF 0
# define FDF_MAX_PROJ_COLF 0xFFFFFF
# define FDF_MIN_PROJ_COLC 0
# define FDF_MAX_PROJ_COLC 0xFFFFFF

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
	t_vertex	***mapi;
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
typedef struct			s_control
{
	int			x;
	int			y;
	int			w;
	int			h;
	t_col		c_bg;
	t_col		c_bd;
	t_col		c_button;
	t_col		c_txt;
	char		*title;
	int			p_nb;
	char		**p_name;
	char		**p_value;
	int			*p_min;
	int			*p_max;
	t_rect		*buttons[2];
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
	void		*mlx;
	void		*win;
	void		*img;
	char		*ptr;
	int			bpp;
	int			sl;
	int			end;
	t_control	*control[3];
	t_map		*map;
}						t_conf;
unsigned int			ft_atoi_hex(char *str);
int						set_error(char *str, int exit);
t_conf					*config_init(int argc, char *argv[]);
void					mlx_control(t_conf *conf);
void					mlx_map(t_conf *conf);
void					mlx_control_put_txt(t_conf *conf);
void					fill_rect(t_conf *conf, t_rect *rect);
#endif
