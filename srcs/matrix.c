/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:31:17 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/17 15:12:03 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	deg2rad(int deg)
{
	return ((double)deg * M_PI / 180.0);
}

double			get_scale(t_conf *conf, int proj)
{
	double		scale;

	if (proj == 1)
	{
		return (fmin
			(double)(FDF_MAP_W)
				/ ((double)conf->mapi->h / sqrt(2.0f) + (double)conf->mapi->w),
				(double)(FDF_MAP_H) / (double)conf->mapi->h / sqrt(2.0f)
		);
	}
}

void			model2view(t_conf *conf, t_vertex *v, double matrix[2][4])
{
	t_vertex	tmp;

	ft_memcpy(&tmp, v, sizeof(t_vertex));
	v->x = matrix[0][0] * tmp->x + matrix[0][1] * tmp->y;
	v->y = matrix[0][2] * tmp->x + matrix[0][3] * tmp->y;
	ft_memcpy(&tmp, v, sizeof(t_vertex));
	v->x = matrix[1][0] * tmp->x;
	v->y = matrix[1][4] * tmp->y;
}

void calc_coord(t_conf *conf, double scale, t_vertex *v)
{

	if (!(conf->maps->vertexes[i][j]))
		conf->maps->vertexes[i][j] = (ini_pointer(sizeof(t_vertexes),
			"Malloc error in calc_coord"));
	ft_memcpy(conf->maps->vertexes[i][j], v, sizeof(t_vertexes));
	conf->maps->vertexes[i][j]->x = (double)(FDF_MAP_X)
		+ (double)(FDF_MAP_W) / 2.0f
		+ v.x * scale + v.y * scale / sqrt(2.0f);
	conf->maps->vertexes[i][j]->y = (double)(FDF_MAP_Y)
		+ (double)(FDF_MAP_H) / 2.0f
		- tmp.y * scale / sqrt(2.0f) - tmp.z;
}

void		view2proj(t_conf *conf, int proj)
{
	int			i;
	int			j;
	double		scale;
	double		max_x;
	double		max_y;

	scale = get_scale(conf, proj);
	max_x = (double)(FDF_MAP_W) / ((double)conf->mapi->h / sqrt(2.0f)
		+ (double)conf->mapi->w);
	max_y = (double)(FDF_MAP_H) / (double)conf->mapi->h / sqrt(2.0f));
	i = -1;
	while (++i < conf->mapi->h)
	{
		j = -1;
		while (++j < conf->mapi->w)
		{
			if (abs(conf->mapt->vertexes[i][j]->x - conf->control->v->x)
				* scale < max_x
				&& abs(conf->mapt->vertexes[i][j]->y - conf->control->v->y)
					* scale	< max_y)
				calc_coord(conf, scale, v);
			else
				ft_mendel((void **)&(conf->maps->vertexes[i][j]))
		}
	}
}
