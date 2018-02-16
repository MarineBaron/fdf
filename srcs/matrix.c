/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:31:17 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/16 18:10:24 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	deg2rad(int deg)
{
	return ((double)deg * M_PI / 180.0);
}

static void		rot_matrix(t_vertex *v, int deg)
{
	double		rot;
	t_vertex	tmp;

	rot = deg2rad(deg);
	ft_memcpy(&tmp, v, sizeof(t_vertex));
	v->x = (tmp.x * cos(rot) - tmp.y * sin(rot));
	v->y = (tmp.x * sin(rot) + tmp.y * cos(rot));
}

static void		trans_matrix(t_conf *conf, t_vertex *v, double x, double y)
{
	t_vertex	tmp;

	ft_memcpy(&tmp, v, sizeof(t_vertex));
	v->x = tmp.x - x;
	v->y = tmp.y - y;
}

void			model2view(t_conf *conf, t_vertex *v)
{
	t_world		*c;

	c = conf->world;
	if (c->x + c->y)
		trans_matrix(conf, v, (double)c->x, (double)c->y);
	if (c->rot != 0)
		rot_matrix(v, c->rot);
}

void		view2proj(t_conf *conf, t_vertex *v)
{
	t_vertex	tmp;

	if (conf->proj->val == 1)
	{
		ft_memcpy(&tmp, v, sizeof(t_vertex));
		v->x = (double)(FDF_MAP_X)
			+ (double)(FDF_MAP_W) / 2.0f
			+ tmp.x * conf->map->scale * (double)conf->world->zoom
			+ tmp.y * conf->map->scale * (double)conf->world->zoom / sqrt(2.0f);
		v->y = (double)(FDF_MAP_Y)
			+ (double)(FDF_MAP_H) / 2.0f
			- tmp.y * conf->map->scale * (double)conf->world->zoom / sqrt(2.0f)
			- tmp.z;
	}
}
