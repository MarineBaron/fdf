/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_map_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 12:41:14 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/28 20:15:57 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

static void	set_limits(t_conf *conf)
{
	int			i;
	int			j;

	conf->mapi->hmin = INT_MAX;
	conf->mapi->hmax = INT_MIN;
	i = -1;
	while (++i < conf->mapi->h)
	{
		j = -1;
		while (++j < conf->mapi->w)
		{
			if (conf->mapi->vtx[i][j]->z > conf->mapi->hmax)
				conf->mapi->hmax = conf->mapi->vtx[i][j]->z;
			if (conf->mapi->vtx[i][j]->z < conf->mapi->hmin)
				conf->mapi->hmin = conf->mapi->vtx[i][j]->z;
		}
	}
	conf->control->v->x = (double)conf->mapi->w / 2.0f;
	conf->control->v->y = (double)conf->mapi->h / 2.0f;
	conf->control->p[0]->max = conf->mapi->w;
	conf->control->p[1]->max = conf->mapi->h;
}

static void	mapi_create(t_conf *conf, t_lstmapi *lstmapi)
{
	t_lstmapi	*tmp;
	int			i;

	conf->mapi->vtx = (t_vtx ***)init_pointer(conf,
		conf->mapi->h * sizeof(t_vtx **), "ErrM (mapi vtx)");
	i = -1;
	while (++i < conf->mapi->h)
		conf->mapi->vtx[i] =
			(t_vtx **)init_pointer(conf, conf->mapi->w * sizeof(t_vtx *),
				"ErrM (mapi vtx)");
	tmp = lstmapi;
	while (lstmapi)
	{
		tmp->vertex->y = (double)conf->mapi->h - tmp->vertex->y - 1.0f;
		conf->mapi->vtx[(int)tmp->vertex->y][(int)tmp->vertex->x] = tmp->vertex;
		tmp = lstmapi->next;
		ft_memdel((void **)&lstmapi);
		lstmapi = tmp;
	}
	set_limits(conf);
}

static void	map_create_maps(t_conf *conf)
{
	conf->mapt = (t_map *)init_pointer(conf, sizeof(t_map), "ErrM (mapt)");
	conf->mapt->vtx = (t_vtx ***)init_pointer(conf,
		conf->mapi->h * sizeof(t_vtx **), "ErrM (mapi vtx)");
	conf->maps = (t_map *)init_pointer(conf, sizeof(t_map), "ErrM (maps");
	conf->maps->vtx = (t_vtx ***)init_pointer(conf,
		conf->mapi->h * sizeof(t_vtx **), "ErrM (mapt vtx)");
}

void		map_create(t_conf *conf, t_lstmapi *lstmapi)
{
	int			i;
	int			j;

	mapi_create(conf, lstmapi);
	map_create_maps(conf);
	i = -1;
	while (++i < conf->mapi->h)
	{
		conf->mapt->vtx[i] = (t_vtx **)init_pointer(conf,
			conf->mapi->w * sizeof(t_vtx *), "ErrM (mapt vtx[i])");
		conf->maps->vtx[i] = (t_vtx **)init_pointer(conf,
			conf->mapi->w * sizeof(t_vtx *), "ErrM (maps vtx[i])");
		j = -1;
		while (++j < conf->mapi->w)
		{
			conf->mapt->vtx[i][j] = (t_vtx *)init_pointer(conf,
				conf->mapi->w * sizeof(t_vtx), "ErrM (mapt vtx[i][j])");
			ft_memcpy(conf->mapt->vtx[i][j], conf->mapi->vtx[i][j],
				sizeof(t_vtx));
			conf->maps->vtx[i][j] = NULL;
		}
	}
}
