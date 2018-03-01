/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model2proj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:31:17 by mbaron            #+#    #+#             */
/*   Updated: 2018/03/01 08:59:23 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_scale(t_conf *conf)
{
	if (conf->control->v->proj == 0)
	{
		conf->control->v->scale = fmin(
			(double)(FDF_MAP_W)
				/ ((double)conf->mapi->h * (M_SQRT1_2) + (double)conf->mapi->w),
				(double)(FDF_MAP_H) / (double)conf->mapi->h * (M_SQRT1_2));
	}
}

static void	is_visible(t_conf *conf, t_vtx *v)
{
	v->visible = 0;
	if (conf->control->v->proj == 0)
	{
		if (fabs(v->y * (M_SQRT1_2)
			* conf->control->v->scale * (double)conf->control->v->zoom)
			> (double)(FDF_MAP_H) / 2.0 - (double)(FDF_MARGE))
			return ;
		if (fabs((v->x + v->y * (M_SQRT1_2))
			* conf->control->v->scale * (double)conf->control->v->zoom)
			> (double)(FDF_MAP_W) / 2.0 - (double)(FDF_MARGE))
			return ;
	}
	v->visible = 1;
}

static void	get_maps_vertex(t_conf *conf, t_vtx *vt, t_vtx *vs)
{
	ft_memcpy(vs, vt, sizeof(t_vtx));
	if (conf->control->v->proj == 0)
	{
		vs->x = FDF_MARGE + (double)(FDF_MAP_W) / 2.0f
			+ vt->x * conf->control->v->scale * (double)conf->control->v->zoom
			+ vt->y * conf->control->v->scale
			* (double)conf->control->v->zoom * (M_SQRT1_2);
		vs->y = FDF_MARGE + (double)(FDF_MAP_H) / 2.0f
			- vt->y * conf->control->v->scale
				* (double)conf->control->v->zoom * (M_SQRT1_2)
			- vt->z * (double)conf->control->v->z;
	}
}

void		model2view(t_conf *conf)
{
	t_vtx		tmp;
	int			i;
	int			j;
	double		**m;

	get_scale(conf);
	m = conf->matrix;
	i = -1;
	while (++i < conf->mapi->h)
	{
		j = -1;
		while (++j < conf->mapi->w)
		{
			tmp = *(conf->mapi->vtx[i][j]);
			conf->mapt->vtx[i][j]->x = tmp.x - m[1][0];
			conf->mapt->vtx[i][j]->y = tmp.y - m[1][3];
			ft_memcpy(&tmp, conf->mapt->vtx[i][j], sizeof(t_vtx));
			conf->mapt->vtx[i][j]->x = m[0][0] * tmp.x + m[0][1] * tmp.y;
			conf->mapt->vtx[i][j]->y = m[0][2] * tmp.x + m[0][3] * tmp.y;
			is_visible(conf, conf->mapt->vtx[i][j]);
		}
	}
}

void		view2proj(t_conf *conf)
{
	int			i;
	int			j;

	i = -1;
	while (++i < conf->mapi->h)
	{
		j = -1;
		while (++j < conf->mapi->w)
		{
			if (conf->mapt->vtx[i][j]->visible)
			{
				if (!(conf->maps->vtx[i][j]))
					conf->maps->vtx[i][j] = (init_pointer(conf, sizeof(t_vtx),
						"Malloc error in get_maps_vertex"));
				get_maps_vertex(conf, conf->mapt->vtx[i][j],
					conf->maps->vtx[i][j]);
			}
			else
				ft_memdel((void **)&(conf->maps->vtx[i][j]));
		}
	}
}
