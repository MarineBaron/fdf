/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:15:57 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/17 15:05:17 by mbaron           ###   ########.fr       */
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
			if (i > 0)
				put_line(conf, conf->map->vertexes[i][j],
					conf->map->vertexes[i - 1][j]);
			if (j < conf->mapi->w - 1)
				put_line(conf, conf->map->vertexes[i][j],
					conf->map->vertexes[i][j + 1]);
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
		return (conf->control->floor);
	if (z == conf->mapi->hmax)
		return (conf->control->ceil);
	p = (z - conf->mapi->hmin) / (conf->mapi->hmax - conf->mapi->hmin);
	r = get_grad_col(conf->control->floor >> 16,
		conf->control->ceil >> 16, p);
	b = get_grad_col((conf->control->floor >> 8) & 0xFF,
		(conf->control->ceil >> 8) & 0xFF, p);
	g = get_grad_col(conf->control->floor & 0xFF,
		conf->control->ceil & 0xFF, p);
	return ((r << 16) | (b << 8) | g);
}

double			**get_matrix(t_values *v)
{
	double		matrix[2][4];
	double		rot;
	double		cosr;
	double		sinr;

	rot = deg2rad(v->rot);
	cosr = cos(rot);
	sinr = sin(rot);
	matrix[0][0] = cosr;
	matrix[0][1] = -sinr;
	matrix[0][2] = sinr;
	matrix[0][3] = cosr;
	matrix[1][0] = v->x;
	matrix[1][1] = 0;
	matrix[1][2] = 0;
	matrix[1][3] = v->y;
	return (matrix);
}

void ini_mapt(t_conf *conf, double matrix[2][4]) {
	int			i;
	int			j;
	t_vertex 	v;

	i = -1;
	while (++i < conf->mapi->h)
	{
		j = -1;
		while (++j < conf->mapi->w)
		{
			v = conf->mapt->vertexes[i][j];
			ft_memcpy(v, conf->mapi->vertexes[i][j],
				sizeof(t_vertex));
			model2view(conf, v, matrix);
			if (conf->control->v->col)
				v->c = map_get_color_gradient(conf, v->z);
		}
	}
}

void set_colors_ini(t_conf *conf) {
	int			i;
	int			j;

	i = -1;
	while (++i < conf->mapi->h)
	{
		j = -1;
		while (++j < conf->mapi->w)
		{
			if (conf->maps->vertexes[i][j])
				conf->maps->vertexes[i][j]->c = conf->mapi->vertexes[i][j]->c;
		}

	}
}

void set_colors_gradient(t_conf *conf) {
	int			i;
	int			j;

	i = -1;
	while (++i < conf->mapi->h)
	{
		j = -1;
		while (++j < conf->mapi->w)
		{
			if (conf->maps->vertexes[i][j])
				conf->maps->vertexes[i][j]->c = map_get_color_gradient(conf,
					conf->maps->vertexes[i][j]->z);
		}
	}
}

void set_colors(t_conf *conf) {
	if (conf->control->n->col != conf->control->v->col)
	{
		if (conf->control->v->col)
			set_colors_gradient(conf);
		else
			set_colors_ini(conf);
	}
	else if (conf->control->n->col
			&& (conf->control->n->floor != conf->control->v->floor
				|| conf->control->n->ceil != conf->control->v->ceil))
		set_colors_gradient(conf);
}

void			set_img_map(t_conf *conf)
{
	int			i;
	int			j;
	double		matrix[2][4];
	double		scale;
	t_vertex	v;

	matrix = conf->control->n
		? get_matrix(conf->control->n) : get_matrix(conf->control->v);

	if (!conf->control->n || (conf->control->n && (conf->control->n->x != conf->control->v->x
		|| conf->control->n->y != conf->control->v->y
		|| conf->control->n->rot != conf->control->v->rot
		|| conf->control->n->proj != conf->control->v->proj)))
	{
		if (!conf->control->n)
			ini_mapt(conf, matrix);
		else if (conf->control->n->proj == conf->control->v->proj)
		{
			model2view(conf, matrix);
			conf->control->v->x = conf->control->n->x;
			conf->control->v->y = conf->control->n->y;
		}
		view2proj(conf, conf->control->n->proj);
	}
	set_colors(conf)
	put_map_vectors(conf);
}
