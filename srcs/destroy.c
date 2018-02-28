/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:59:32 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/28 20:24:51 by mbaron           ###   ########.fr       */
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
		{
			ft_memdel((void **)&conf->mapi->vtx[i][j]);
			ft_memdel((void **)&conf->mapt->vtx[i][j]);
			ft_memdel((void **)&conf->maps->vtx[i][j]);
		}
		ft_memdel((void **)&conf->mapi[i]);
		ft_memdel((void **)&conf->mapt[i]);
		ft_memdel((void **)&conf->maps[i]);
	}
	ft_memdel((void **)&conf->mapi);
	ft_memdel((void **)&conf->mapt);
	ft_memdel((void **)&conf->maps);
}

void		destroy_img(t_conf *conf, t_img *img)
{
	mlx_destroy_image(conf->mlx, img->img);
	ft_memdel((void **)&img);
}

void		destroy(t_conf *conf)
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
