/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 09:24:52 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/16 18:20:53 by mbaron           ###   ########.fr       */
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
		p = conf->control->params[i];
		ft_memdel((void **)&p->name);
		ft_memdel((void **)&p->pos_v);
		ft_memdel((void **)&p->buttons[0]);
		ft_memdel((void **)&p->buttons[1]);
		ft_memdel((void **)&p->buttons);
	}
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
			ft_memdel((void **)&conf->mapi->vertexes[i][j]);
		ft_memdel((void **)&conf->mapi->vertexes[i]);
	}
	ft_memdel((void **)&conf->mapi->vertexes);
	ft_memdel((void **)&conf->mapi);
	ft_memdel((void **)&conf->map);
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
}

void	destroy_img(t_conf *conf, t_img *img)
{
	mlx_destroy_image(conf->mlx, img->img);
	ft_memdel((void **)&img);
}

static t_img	*init_img(t_conf *conf, int w, int h)
{
	t_img  *img;
	
	img = (t_img *)init_pointer(sizeof(t_img),
		"init_img");
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
	conf->i_control = (t_img *)init_pointer(sizeof(t_img),
		"Error malloc in config_default (i_control)");
	conf->i_map = (t_img *)init_pointer(sizeof(t_img),
		"Error malloc in config_default (i_control)");
	conf->i_value = (t_img *)init_pointer(sizeof(t_img),
		"Error malloc in config_default (i_control)");
	conf->i_btn = (t_img *)init_pointer(sizeof(t_img),
		"Error malloc in config_default (i_control)");
	conf->i_map = init_img(conf, FDF_MAP_W, FDF_MAP_H);
	conf->i_control = init_img(conf, FDF_CL_W, FDF_CL_HT);
	conf->i_value = init_img(conf, FDF_CL_C_W * 2, FDF_CL_HT);
	conf->i_btn = init_img(conf, FDF_CL_C_W, FDF_CL_C_H);
}

void	clear_screen(t_conf *conf)
{
	t_rect *rect;
	
	rect = get_rect(0, 0, conf->i_value->w, conf->i_value->h);
	rect->c_bg = FDF_CL_BG_COLOR;
	fill_rect(conf->i_value, rect);
	ft_memdel((void **)rect);
	rect = get_rect(0, 0, conf->i_map->w, conf->i_map->h);
	rect->c_bg = FDF_CL_BG_COLOR;
	fill_rect(conf->i_map, rect);
	ft_memdel((void **)rect);
}

void	render(t_conf *conf, int c_index, int new)
{
	if (!conf->mlx)
	{
		render_init(conf);
		put_control_init(conf);
		destroy_img(conf, conf->i_control);
		
	}
	clear_screen(conf);
	put_control_values(conf);
	mlx_put_image_to_window(conf->mlx, conf->win, conf->i_map->img,
		FDF_MAP_X, FDF_MAP_Y);
	set_img_map(conf, c_index, new);
}

int		main(int argc, char *argv[])
{
	t_conf	*conf;

	if (!(conf = config_init(argc, argv)))
		return (1);
	ft_putendl("Config is OK, you can play !!!");
	render(conf, -1, 0);
	/*
	mlx_key_hook(conf->win, hook_key, conf);
	mlx_mouse_hook(conf->win, hook_mouse, conf);
		*/
	mlx_loop(conf->mlx);
	destroy(conf);
	return (0);
}
