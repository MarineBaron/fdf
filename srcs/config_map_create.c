/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_map_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 12:41:14 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/27 17:20:09 by mbaron           ###   ########.fr       */
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

	conf->mapi->vtx = (t_vertex ***)init_pointer(
		conf->mapi->h * sizeof(t_vertex **),
		"Malloc error in map_create (vertexes)");
	i = -1;
	while (++i < conf->mapi->h)
		conf->mapi->vtx[i] =
			(t_vertex **)init_pointer(conf->mapi->w
				* sizeof(t_vertex *),
				"Malloc error in map_create (vertexes[i])");
	tmp = lstmapi;
	while (lstmapi)
	{
		tmp->vertex->y = (double)conf->mapi->h
			- tmp->vertex->y - 1.0f;
		conf->mapi->vtx[(int)tmp->vertex->y]
			[(int)tmp->vertex->x] = tmp->vertex;
		tmp = lstmapi->next;
		ft_memdel((void **)&lstmapi);
		lstmapi = tmp;
	}
}

void		map_create(t_conf *conf, t_lstmapi *lstmapi)
{
	int			i;
	int			j;

	mapi_create(conf, lstmapi);
	set_limits(conf);
	conf->mapt = (t_map *)init_pointer(sizeof(t_map),
		"Malloc error in map_create (conf->mapt)");
	conf->mapt->vtx = (t_vertex ***)init_pointer(
		conf->mapi->h * sizeof(t_vertex **),
		"Malloc error in map_create (vertexes)");
	conf->maps = (t_map *)init_pointer(sizeof(t_map),
		"Malloc error in map_create (conf->maps)");
	conf->maps->vtx = (t_vertex ***)init_pointer(
		conf->mapi->h * sizeof(t_vertex **),
		"Malloc error in map_create (vertexes)");
	i = -1;
	while (++i < conf->mapi->h)
	{
		conf->mapt->vtx[i] = (t_vertex **)init_pointer(
			conf->mapi->w * sizeof(t_vertex *),
			"Malloc error in map_create (vertexes[i])");
		conf->maps->vtx[i] = (t_vertex **)init_pointer(
			conf->mapi->w * sizeof(t_vertex *),
			"Malloc error in map_create (vertexes[i])");
		j = -1;
		while (++j < conf->mapi->w)
		{
			conf->mapt->vtx[i][j] = (t_vertex *)init_pointer(
				conf->mapi->w * sizeof(t_vertex),
				"Malloc error in map_create (vertexes[i][j])");
			ft_memcpy(conf->mapt->vtx[i][j],
				conf->mapi->vtx[i][j], sizeof(t_vertex));
			conf->maps->vtx[i][j] = NULL;
		}
	}
	conf->mapt->scale = fmin((double)(FDF_MAP_W)
		/ ((double)conf->mapi->h * (M_SQRT1_2) + (double)conf->mapi->w),
		(double)(FDF_MAP_H) / (double)conf->mapi->h * (M_SQRT1_2));
}
