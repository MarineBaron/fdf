/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:30:45 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/28 20:23:11 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		set_colors_ini(t_conf *conf)
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
				conf->maps->vtx[i][j]->c = conf->mapi->vtx[i][j]->c;
		}
	}
}

int				get_grad_col(int co, int cd, double p)
{
	if (co == cd)
		return (co);
	return ((int)((double)co + ((double)cd - (double)(co)) * p));
}

static t_col	map_get_color_gradient(t_conf *conf, double z)
{
	double		p;
	int			r;
	int			g;
	int			b;

	if (z == conf->mapi->hmin)
		return (conf->control->v->floor);
	if (z == conf->mapi->hmax)
		return (conf->control->v->ceil);
	p = (z - conf->mapi->hmin) / (conf->mapi->hmax - conf->mapi->hmin);
	r = get_grad_col(conf->control->v->floor >> 16,
		conf->control->v->ceil >> 16, p);
	b = get_grad_col((conf->control->v->floor >> 8) & 0xFF,
		(conf->control->v->ceil >> 8) & 0xFF, p);
	g = get_grad_col(conf->control->v->floor & 0xFF,
		conf->control->v->ceil & 0xFF, p);
	return ((r << 16) | (b << 8) | g);
}

static void		set_colors_gradient(t_conf *conf)
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
				conf->maps->vtx[i][j]->c = map_get_color_gradient(conf,
					conf->maps->vtx[i][j]->z);
		}
	}
}

void			set_colors(t_conf *conf)
{
	if (conf->control->v->col)
		set_colors_gradient(conf);
	else
		set_colors_ini(conf);
}
