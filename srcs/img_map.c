/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:15:57 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/27 17:34:43 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			set_img_map_vectors(t_conf *conf)
{
	int			i;
	int			j;

	i = -1;
	while (++i < conf->mapi->h)
	{
		j = -1;
		while (++j < conf->mapi->w)
		{
			if (i > 0 && conf->mapt->vtx[i][j]->visible
				&& conf->mapt->vtx[i - 1][j]->visible)
				put_line(conf, conf->maps->vtx[i][j],
						conf->maps->vtx[i - 1][j]);
			if (j < conf->mapi->w - 1 && conf->mapt->vtx[i][j]->visible
				&& conf->mapt->vtx[i][j + 1]->visible)
				put_line(conf, conf->maps->vtx[i][j],
						conf->maps->vtx[i][j + 1]);
		}
	}
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

double			**matrix_init(t_values *v)
{
	double		**matrix;

	matrix = (double **)init_pointer(2 * sizeof(double *),
		"Malloc error in get_matrix");
	matrix[0] = (double *)init_pointer(4 * sizeof(double),
		"Malloc error in get_matrix");
	matrix[1] = (double *)init_pointer(4 * sizeof(double),
		"Malloc error in get_matrix");
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[0][3] = 1;
	matrix[1][0] = v->x;
	matrix[1][1] = 0;
	matrix[1][2] = 0;
	matrix[1][3] = v->y;
	return (matrix);
}

void			set_colors_ini(t_conf *conf)
{
	int			i;
	int			j;

	i = -1;
	while (++i < conf->mapi->h)
	{
		j = -1;
		while (++j < conf->mapi->w)
		{
			if (conf->maps->vtx[i][j])
				conf->maps->vtx[i][j]->c = conf->mapi->vtx[i][j]->c;
		}
	}
}

void			set_colors_gradient(t_conf *conf)
{
	int			i;
	int			j;

	i = -1;
	while (++i < conf->mapi->h)
	{
		j = -1;
		while (++j < conf->mapi->w)
		{
			if (conf->maps->vtx[i][j])
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

void			set_img_map(t_conf *conf)
{
	t_control *c;

	c = conf->control;
	if (!c->n)
	{
		conf->matrix = matrix_init(c->v);
		model2view(conf);
		view2proj(conf);
	}
	else if (c->n->x != c->v->x || c->n->y != c->v->y
		|| c->n->rot != c->v->rot || c->n->zoom != c->v->zoom)
	{
		ft_memcpy(c->v, c->n, sizeof(t_values));
		model2view(conf);
		view2proj(conf);
	}
	else if (c->n->z != c->v->z || c->n->proj != c->v->proj)
	{
		ft_memcpy(c->v, c->n, sizeof(t_values));
		view2proj(conf);
	}
	set_colors(conf);
	set_img_map_vectors(conf);
}
