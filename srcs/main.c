/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 09:24:52 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/08 09:13:03 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	destroy_control(t_conf *conf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		ft_memdel((void **)&conf->control[i]->title);
		ft_memdel((void **)&conf->control[i]->pos_title);
		j = -1;
		while (++j < conf->control[i]->p_nb)
		{
			ft_memdel((void **)&conf->control[i]->params[j]->name);
			ft_memdel((void **)&conf->control[i]->params[j]->pos_param);
			ft_memdel((void **)&conf->control[i]->params[j]->pos_value);
			ft_memdel((void **)&conf->control[i]->params[j]->buttons[0]);
			ft_memdel((void **)&conf->control[i]->params[j]->buttons[1]);
			ft_memdel((void **)&conf->control[i]->params[j]->buttons);
		}
		ft_memdel((void **)&conf->control[i]);
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
	ft_memdel((void **)&conf->world);
	ft_memdel((void **)&conf->camera);
	ft_memdel((void **)&conf->proj);
	ft_memdel((void **)&conf->color);
	destroy_map(conf);
	mlx_destroy_image(conf->mlx, conf->img);
	ft_memdel((void **)&conf->img);
	mlx_destroy_window(conf->mlx, conf->win);
	ft_memdel((void **)&conf->win);
	ft_memdel((void **)&conf->mlx);
}

void	render(t_conf *conf)
{
	if (!conf->mlx)
	{
		ft_putendl("Init MLX");
		if (!(conf->mlx = mlx_init()))
			set_error("Echec in MLX init", 1);
		if (!conf->win && !(conf->win = mlx_new_window(conf->mlx,
			FDF_WIN_W, FDF_WIN_H, "My map")))
			set_error("Echec in MLX new window", 1);
		if (!conf->img && !(conf->img = mlx_new_image(conf->mlx,
			FDF_WIN_W, FDF_WIN_H)))
			set_error("Echec in MLX new image", 1);
		conf->ptr = mlx_get_data_addr(conf->img, &conf->bpp, &conf->sl,
			&conf->end);
		conf->bpp /= 8;
		set_img_control(conf);
	}
	ft_putendl("Render");
	set_img_clear(conf);
	set_img_control_value(conf);
	set_img_map(conf);
	mlx_put_image_to_window(conf->mlx, conf->win, conf->img, 0, 0);
	set_txt_control(conf);
	set_txt_control_value(conf);
}

int			main(int argc, char *argv[])
{
	t_conf	*conf;

	conf = NULL;
	if (!(conf = config_init(argc, argv)))
		return (1);
	ft_putendl("Config is OK, you can play !!!");
	render(conf);
	mlx_key_hook(conf->win, hook_key, conf);
	mlx_mouse_hook(conf->win, hook_mouse, conf);
	mlx_loop(conf->mlx);
	destroy(conf);
	return (0);
}
