/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 09:24:52 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/27 17:12:23 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	destroy_control(t_conf *conf)
{
	int		i;
	t_param *p;

	i = -1;
	while (++i < conf->control->nb)
	{
		p = conf->control->p[i];
		ft_memdel((void **)&p->name);
		ft_memdel((void **)&p->pos_v);
		ft_memdel((void **)&p->buttons[0]);
		ft_memdel((void **)&p->buttons[1]);
		ft_memdel((void **)&p->buttons);
	}
	ft_memdel((void **)&conf->control->v);
	ft_memdel((void **)&conf->control->n);
	ft_memdel((void **)&conf->control);
}

static void	destroy_map(t_conf *conf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < conf->mapi->h)
	{
		j = -1;
		while (++j < conf->mapi->w)
			ft_memdel((void **)&conf->mapi->vtx[i][j]);
		ft_memdel((void **)&conf->mapi[i]);
	}
	ft_memdel((void **)&conf->mapi);
	ft_memdel((void **)&conf->mapi);
	ft_memdel((void **)&conf->mapt);
}

static void	destroy(t_conf *conf)
{
	destroy_control(conf);
	destroy_map(conf);
	destroy_img(conf, conf->i_btn);
	destroy_img(conf, conf->i_value);
	destroy_img(conf, conf->i_map);
	mlx_destroy_window(conf->mlx, conf->win);
	ft_memdel((void **)&conf->mlx);
	ft_memdel((void **)&conf->matrix);
	ft_memdel((void **)&conf->mouse);
}

void	destroy_img(t_conf *conf, t_img *img)
{
	mlx_destroy_image(conf->mlx, img->img);
	ft_memdel((void **)&img);
}

static t_img	*init_img(t_conf *conf, int w, int h)
{
	t_img	*img;

	img = (t_img *)init_pointer(sizeof(t_img), "init_img");
	if (!img->img && !(img->img = mlx_new_image(conf->mlx, w, h)))
		set_error("Echec in MLX new image (map)", 1);
	img->ptr = mlx_get_data_addr(img->img, &(img->bpp),
		&(img->sl), &(img->end));
	img->bpp /= 8;
	img->w = w;
	img->h = h;
	return (img);
}

static void	render_init(t_conf *conf)
{
	ft_putendl("Init MLX");
	if (!(conf->mlx = mlx_init()))
		set_error("Echec in MLX init", 1);
	if (!conf->win && !(conf->win = mlx_new_window(conf->mlx,
		FDF_WIN_W, FDF_WIN_H, "My Map")))
		set_error("Echec in MLX new window", 1);
	conf->i_control = (t_img *)init_pointer(sizeof(t_img), "ErrM (i_control)");
	conf->i_map = (t_img *)init_pointer(sizeof(t_img), "ErrM (i_map)");
	conf->i_value = (t_img *)init_pointer(sizeof(t_img), "ErrM (i_value)");
	conf->i_btn = (t_img *)init_pointer(sizeof(t_img), "ErrM (i_btn)");
	conf->i_map = init_img(conf, FDF_MAP_W, FDF_MAP_H);
	conf->i_control = init_img(conf, FDF_CL_W, FDF_CL_HT);
	conf->i_value = init_img(conf, (FDF_CL_C_W) * 2, FDF_CL_HT);
	conf->i_btn = init_img(conf, FDF_CL_C_W, FDF_CL_C_H);
	conf->keypressed = 0;
	conf->mouse = (t_mouse *)init_pointer(sizeof(t_mouse), "ErrM (mouse)");
	mouse_init(conf->mouse);
}

void	clear_screen(t_conf *conf)
{
	t_rect *rect;

	rect = get_rect(0, 0, conf->i_value->w, conf->i_value->h);
	rect->c_bg = FDF_CL_BG_COLOR;
	fill_rect(conf->i_value, rect);
	mlx_put_image_to_window(conf->mlx, conf->win, conf->i_value->img,
		FDF_CL_V_X, FDF_CL_X + FDF_CL_H);
	ft_memdel((void **)rect);
	rect = get_rect(0, 0, conf->i_map->w, conf->i_map->h);
	rect->c_bg = FDF_CL_BG_COLOR;
	fill_rect(conf->i_map, rect);
	ft_memdel((void **)rect);
}

void	render(t_conf *conf)
{
	if (!conf->mlx)
	{
		render_init(conf);
		put_control_init(conf);
		destroy_img(conf, conf->i_control);
	}
	clear_screen(conf);
	put_control_values(conf);
	set_img_map(conf);
	mlx_put_image_to_window(conf->mlx, conf->win, conf->i_map->img,
		FDF_MAP_X, FDF_MAP_Y);
}

int		main(int argc, char *argv[])
{
	t_conf	*conf;

	if (!(conf = config_init(argc, argv)))
		return (1);
	ft_putendl("Config is OK, you can play !!!");
	render(conf);
	mlx_hook(conf->win, 2, 0, hook_keydown, conf);
	mlx_hook(conf->win, 3, 0, hook_keyup, conf);
	mlx_hook(conf->win, 4, 0, hook_mousedown, conf);
	mlx_hook(conf->win, 5, 0, hook_mouseup, conf);
	mlx_hook(conf->win, 6, 0, hook_mousemove, conf);
	mlx_hook(conf->win, 17, 0, hook_close, conf);
	mlx_loop(conf->mlx);
	destroy(conf);
	return (0);
}
