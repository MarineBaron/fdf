/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 09:23:07 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/04 23:42:01 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# define FDF_WIN_W 1000
# define FDF_WIN_H 800
# define FDF_MARGE 10
# define FDF_CONTROL_W 200 - 2 * FDF_MARGE
# define FDF_CONTROL_X FDF_MARGE
# define FDF_CONTROL_Y FDF_MARGE
# define FDF_MAP_W FDF_WIN_W - FDF_CONTROL_W - 3 * FDF_MARGE
# define FDF_MAP_H FDF_WIN_H - 2 * FDF_MARGE
# define FDF_MAP_X FDF_CONTROL_W
# define FDF_MAP_Y FDF_MARGE
# define FDF_CONTROL_MARGE 2
# define FDF_CONTROL_H 20
# define FDF_CONTROL_C_W FDF_CONTROL_H - 2 * FDF_CONTROL_MARGE
# define FDF_CONTROL_C_H FDF_CONTROL_C_W
# define FDF_CONTROL_V_W FDF_CONTROL_C_W
# define FDF_CONTROL_C2_X FDF_CONTROL_W - FDF_CONTROL_MARGE - FDF_CONTROL_C_W
# define FDF_CONTROL_C1_X FDF_CONTROL_C2_X - FDF_CONTROL_MARGE - FDF_CONTROL_C_W
# define FDF_CONTROL_V_X FDF_CONTROL_C1_X - FDF_CONTROL_MARGE - FDF_CONTROL_V_W
# define FDF_CONTROL_P_X FDF_MARGE + FDF_CONTROL_MARGE
# define FDF_WIN_BG_COLOR 0x000000
# define FDF_CONTROL_BG_COLOR 0x202020
# define FDF_CONTROL_BD_COLOR 0x303030
# define FDF_CONTROL_BUTTON1_COLOR 0x404040
# define FDF_CONTROL_BUTTON2_COLOR 0x505050
# define FDF_CONTROL_TXT1_COLOR 0xA0A0A0
# define FDF_CONTROL_TXT2_COLOR 0xC0C0C0
# define FDF_PARAM_NB_WORLD 5
# define FDF_PARAM_NB_CAMERA 6
# define FDF_PARAM_NB_PROJ 4

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
}				t_vector;
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
typedef struct			s_mba_img
{
	int		x;
	int		y;
	int		w;
	int		h;
	void	*mlx;
	int		bpp;
	int		sl;
	int		ent;
	t_col	c_bg;
	t_col	c_bd;
}						t_mba_img;
typedef struct			s_control_c
{
	int		x;
	int		y;
	int		w;
	int		h;
	t_col	c_bg;
	t_col	c_bd;
	t_col	c_button;
	t_col	c_txt;
	char	*title;
	int		p_nb;
	char	**p_name;
	char	**p_value;
	t_img	*i_value;
	t_img	*i_control;
}						t_control_c;
typedef struct			s_control
{
	int			x;
	int			y;
	int			w;
	int			h;
	t_control_c	*control[3];
}						t_control;
typedef struct			s_map
{
	t_img		*map;
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
	t_control	*control;
	t_map		*map;
}						t_conf;
unsigned int			ft_atoi_hex(char *str);
int						set_error(char *str, int exit);
t_conf					*config_init(int argc, char *argv[]);
void					mlx_control_init(t_conf *conf);
void					mlx_map_init(t_conf *conf);
#endif
