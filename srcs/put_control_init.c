/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_control_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:24:38 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/16 17:34:06 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_rect		*get_rect(int x, int y, int w, int h)
{
	t_rect	*rect;

	rect = (t_rect *)init_pointer(sizeof(t_rect), "Malloc error in get_rect");
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return (rect);
}

static void	put_control_init_img_buttons_xpm(t_conf *conf, t_rect *rect,
	char *url)
{
	void	*img;
	int		w;
	int		h;

	if (!(img = mlx_xpm_file_to_image(conf->mlx, url, &w, &h)))
		set_error("Echec in MLX buttons xpm (button)", 1);
	mlx_put_image_to_window(conf->mlx, conf->win, img,
		FDF_CL_C_DEC + rect->x, FDF_CL_C_DEC + rect->y);
	mlx_destroy_image(conf->mlx, img);
}

static char	*get_button_url(int i)
{
	int		d;
	int		m;

	d = i / 2;
	m = i % 2;
	if (!d)
		return (m ? "./buttons/right.xpm" : "./buttons/left.xpm");
	if (d == 1)
		return (m ? "./buttons/up.xpm" : "./buttons/down.xpm");
	if (d == 3)
		return (m ? "./buttons/turn_up.xpm" : "./buttons/turn_down.xpm");
	return (m ? "./buttons/plus.xpm" : "./buttons/minus.xpm");
}

static void	put_control_init_img_buttons(t_conf *conf)
{
	t_rect	*rect;
	int		i;

	rect = get_rect(0, 0, conf->i_btn->w, conf->i_btn->h);
	rect->c_bg = FDF_CL_BTN1_COLOR;
	fill_rect(conf->i_btn, rect);
	rect->y = FDF_CL_Y + FDF_CL_H + FDF_CL_MARGE;
	i = -1;
	while (++i < 2 * conf->control->nb)
	{
		rect->x = (i & 1) ? FDF_CL_C2_X : FDF_CL_C1_X;
		mlx_put_image_to_window(conf->mlx, conf->win, conf->i_btn->img,
			rect->x, rect->y);
		put_control_init_img_buttons_xpm(conf, rect, get_button_url(i));
		if (i & 1)
			rect->y += FDF_CL_H;
	}
	ft_memdel((void **)&rect);
}

static void	put_control_init_img_control(t_conf *conf)
{
	t_rect	*rect;

	rect = get_rect(0, 0, conf->i_control->w, conf->i_control->h);
	rect->c_bg = FDF_CL_BG_COLOR;
	fill_rect(conf->i_control, rect);
	mlx_put_image_to_window(conf->mlx, conf->win, conf->i_control->img,
		FDF_CL_X, FDF_CL_Y + FDF_CL_H);
	ft_memdel((void **)&rect);
}

void		put_control_init(t_conf *conf)
{
	int		i;
	int		y;

	put_control_init_img_control(conf);
	put_control_init_img_buttons(conf);
	i = -1;
	y = FDF_CL_Y + FDF_CL_MARGE;
	mlx_string_put(conf->mlx, conf->win,
		FDF_CL_X + FDF_CL_MARGE, y,
		FDF_CL_TXT2_COLOR, "Parameters");
	y += FDF_CL_H;
	while (++i < conf->control->nb)
	{
		mlx_string_put(conf->mlx, conf->win,
			FDF_CL_X + FDF_CL_MARGE, y,
			FDF_CL_TXT1_COLOR, conf->control->params[i]->name);
		y += FDF_CL_H;
	}
}
