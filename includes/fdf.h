/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 09:23:07 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/16 17:33:31 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <limits.h>
# include <math.h>
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
	double		hmin;
	double		hmax;
	t_vertex	***vertexes;
}						t_mapi;
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
	int			kdn;
	int			kup;
	t_rect		*pos_v;
	t_rect		**buttons;
}						t_param;
typedef struct			s_control
{
	char		*title;
	int			nb;
	int			x;
	int			y;
	int			z;
	int			rot;
	int			zoom;
	int			proj;
	int			col;
	int			floor;
	int			ceil;
	t_param		**params;
}						t_control;
typedef struct			s_map
{
	t_rect		*rect;
	double		scale;
	t_vertex	***vertexes;
}						t_map;
typedef struct	s_img
{
	void	*img;
	char	*ptr;
	int		bpp;
	int		sl;
	int		end;
	int		w;
	int		h;
}				t_img;
typedef struct			s_conf
{
	t_control	*control;
	t_mapi		*mapi;
	t_map		*map;
	t_map		*screen;
	void		*mlx;
	void		*win;
	t_img		*i_map;
	t_img		*i_control;
	t_img		*i_value;
	t_img		*i_btn;
}						t_conf;
t_conf					*config_init(int argc, char *argv[]);
void					put_control_init(t_conf *conf);
void					set_img_control(t_conf *conf);
void					set_img_control_value(t_conf *conf);
void					set_txt_control(t_conf *conf);
void					set_txt_control_value(t_conf *conf);
void					set_buttons_imgs(t_conf *conf);
void					set_img_clear(t_conf *conf);
void					set_img_map(t_conf *conf);
void					model2view(t_conf *conf, t_vertex *v);
void					view2proj(t_conf *conf, t_vertex *v);
void					render(t_conf *conf);
t_rect					*get_rect(int x, int y, int w, int h);
void					put_rect_win(void *img, t_rect *rect);
void					clear_screen(t_conf *conf);
void					put_control_values(t_conf *conf);
void					put_line(t_conf *conf, t_vector *v);
int						hook_key(int key, t_conf *conf);
int						hook_mouse(int button, int x, int y, t_conf *conf);
void					destroy_img(t_conf *conf, t_img *img);
unsigned int			ft_atoi_hex(char *str);
int						get_grad_col(int co, int cd, double p);
int						set_error(char *str, int exit);
void					*init_pointer(size_t size, char *str_error);
void					fill_rect(t_img *img, t_rect *rect);
#endif
