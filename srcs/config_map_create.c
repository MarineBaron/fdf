/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_map_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 12:41:14 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/15 15:20:07 by mbaron           ###   ########.fr       */
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
			if (conf->mapi->vertexes[i][j]->z > conf->mapi->hmax)
				conf->mapi->hmax = conf->mapi->vertexes[i][j]->z;
			if (conf->mapi->vertexes[i][j]->z < conf->mapi->hmin)
				conf->mapi->hmin = conf->mapi->vertexes[i][j]->z;
		}
	}
	conf->control->x = (double)conf->mapi->w / 2.0f;
	conf->control->y = (double)conf->mapi->h / 2.0f;
	conf->control[0]->max = conf->mapi->w;
	conf->control[1]->max = conf->mapi->h;
}

static void	mapi_create(t_conf *conf, t_lstmapi *lstmapi)
{
	t_lstmapi	*tmp;
	int			i;

	conf->mapi->vertexes = (t_vertex ***)init_pointer(
		conf->mapi->h * sizeof(t_vertex **),
		"Malloc error in map_create (vertexes)");
	i = -1;
	while (++i < conf->mapi->h)
		conf->mapi->vertexes[i] = (t_vertex **)init_pointer(conf->mapi->w
			* sizeof(t_vertex *), "Malloc error in map_create (vertexes[i])");
	tmp = lstmapi;
	while (lstmapi)
	{
		tmp->vertex->y = (double)conf->mapi->h - tmp->vertex->y - 1.0f;
		conf->mapi->vertexes[(int)tmp->vertex->y]
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
	conf->map = (t_map *)init_pointer(sizeof(t_map),
		"Malloc error in map_create (conf->map)");
	conf->map->vertexes = (t_vertex ***)init_pointer(
		conf->mapi->h * sizeof(t_vertex **),
		"Malloc error in map_create (vertexes)");
	i = -1;
	while (++i < conf->mapi->h)
	{
		conf->map->vertexes[i] = (t_vertex **)init_pointer(
			conf->mapi->w * sizeof(t_vertex *),
			"Malloc error in map_create (vertexes[i])");
		j = -1;
		while (++j < conf->mapi->w)
		{
			conf->map->vertexes[i][j] = (t_vertex *)init_pointer(
				conf->mapi->w * sizeof(t_vertex),
				"Malloc error in map_create (vertexes[i][j])");
			ft_memcpy(conf->map->vertexes[i][j],
				conf->mapi->vertexes[i][j], sizeof(t_vertex));
		}
	}
	conf->map->scale = fmin((double)(FDF_MAP_W)
		/ ((double)conf->mapi->h / sqrt(2.0f) + (double)conf->mapi->w),
		(double)(FDF_MAP_H) / (double)conf->mapi->h / sqrt(2.0f));
}
