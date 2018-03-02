/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:19:14 by mbaron            #+#    #+#             */
/*   Updated: 2018/03/02 09:39:48 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	**matrix_init(t_conf *conf, t_values *v)
{
	double		**matrix;
	double		rot;
	double		cosr;
	double		sinr;

	matrix = (double **)init_pointer(conf, 2 * sizeof(double *), "ErrM matrix");
	matrix[0] = (double *)init_pointer(conf, 4 * sizeof(double), "ErrM matrix");
	matrix[1] = (double *)init_pointer(conf, 4 * sizeof(double), "ErrM matrix");
	rot = deg2rad(conf->control->v->rot);
	cosr = cos(rot);
	sinr = sin(rot);
	matrix[0][0] = cosr;
	matrix[0][1] = -sinr;
	matrix[0][2] = -sinr;
	matrix[0][3] = cosr;
	matrix[1][0] = v->x;
	matrix[1][1] = 0;
	matrix[1][2] = 0;
	matrix[1][3] = v->y;
	return (matrix);
}

void	matrix_change_orig(t_conf *conf, int hor, int add)
{
	double x;
	double y;

	if (!hor)
	{
		x = (add ? -1.0 : 1.0) / (double)conf->control->v->zoom;
		y = 0;
	}
	else
	{
		x = (add ? 1.0 : -1.0) / (double)conf->control->v->zoom;
		y = (add ? -1.0 : 1.0) / (double)conf->control->v->zoom * M_SQRT2;
	}
	conf->matrix[1][0] += (conf->matrix[0][3] * x + conf->matrix[0][2] * y);
	conf->matrix[1][3] += (conf->matrix[0][1] * x + conf->matrix[0][0] * y);
	conf->control->n->x = conf->matrix[1][0];
	conf->control->n->y = conf->matrix[1][3];
}

void	matrix_change_xy(t_conf *conf, int xm, int ym)
{
	double x;
	double y;

	y = ((double)(ym - conf->mouse->y)
		/ (double)conf->control->v->zoom / conf->control->v->scale
		* M_SQRT2);
	x = ((double)(conf->mouse->x - xm) + (double)(conf->mouse->y - ym))
		/ (double)conf->control->v->zoom / conf->control->v->scale;
	conf->matrix[1][0] += conf->matrix[0][3] * x + conf->matrix[0][2] * y;
	conf->matrix[1][3] += conf->matrix[0][1] * x + conf->matrix[0][0] * y;
	conf->control->n->x = conf->matrix[1][0];
	conf->control->n->y = conf->matrix[1][3];
	render(conf);
}

void	matrix_change_rot(t_conf *conf, int add)
{
	double		rot;
	double		cosr;
	double		sinr;

	conf->control->n->rot = (conf->control->v->rot + (add ? 1 : -1));
	if (conf->control->n->rot > 359)
		conf->control->n->rot = 0;
	else if (conf->control->n->rot < 0)
		conf->control->n->rot = 359;
	rot = deg2rad(conf->control->n->rot);
	cosr = cos(rot);
	sinr = sin(rot);
	conf->matrix[0][0] = cosr;
	conf->matrix[0][1] = -sinr;
	conf->matrix[0][2] = sinr;
	conf->matrix[0][3] = cosr;
}
