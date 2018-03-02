/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:27:46 by mbaron            #+#    #+#             */
/*   Updated: 2018/03/02 18:17:56 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		poly_set_limitx(t_poly *poly)
{
	int		k;

	poly->minsx = INT_MAX;
	poly->maxsx = INT_MIN;
	k = -1;
	while (++k < 4)
	{
		poly->minsx = (int)fmin(poly->minsx, poly->vtx[k]->x);
		poly->maxsx = (int)fmax(poly->maxsx, poly->vtx[k]->x);
	}
}

static t_poly	*polygone_ini(t_conf *conf, int i, int j)
{
	t_poly	*poly;

	poly = (t_poly*)init_pointer(conf, sizeof(t_poly), "ErrM t_poly (tmp)");
	poly->next = NULL;
	poly->vtx[0] = conf->maps->vtx[i][j];
	poly->vtx[1] = conf->maps->vtx[i][j - 1];
	poly->vtx[2] = conf->maps->vtx[i + 1][j - 1];
	poly->vtx[3] = conf->maps->vtx[i + 1][j];
	poly->i = i;
	poly->j = j;
	poly_set_limitx(poly);
	return (poly);
}

void			polygone_insert(t_conf *conf, int i, int j)
{
	t_poly	*poly;
	t_poly	*cur;
	t_poly	*prec;

	poly = polygone_ini(conf, i, j);
	cur = conf->pls;
	prec = NULL;
	if (conf->control->v->rot > 0 && conf->control->v->rot < 36)
	{
		while (cur && (poly->i > cur->i
			|| (poly->i == cur->i && poly->j < cur->j)))
		{
			prec = cur;
			cur = cur->next;
		}
	}
	else if (conf->control->v->rot > 35 && conf->control->v->rot < 126)
	{
		while (cur && (poly->i > cur->i
			|| (poly->i == cur->i && poly->j > cur->j)))
		{
			prec = cur;
			cur = cur->next;
		}
	}
	else if (conf->control->v->rot > 125 && conf->control->v->rot < 176)
	{
		// while (cur && (poly->j > cur->j
		// 	|| (poly->j == cur->j && poly->i < cur->i)))
		while (cur && (poly->i < cur->i
			|| (poly->i == cur->i && poly->j > cur->j)))
		{
			prec = cur;
			cur = cur->next;
		}
	}
	else if (conf->control->v->rot > 175 && conf->control->v->rot < 216)
	{
		while (cur && (poly->i < cur->i
			|| (poly->i == cur->i && poly->j > cur->j)))
		{
			prec = cur;
			cur = cur->next;
		}
	}
	else if (conf->control->v->rot > 215 && conf->control->v->rot < 306)
	{
		while (cur && (poly->i < cur->i
			|| (poly->i == cur->i && poly->j < cur->j)))
		{
			prec = cur;
			cur = cur->next;
		}
	}
	else if (conf->control->v->rot > 305 && conf->control->v->rot < 336)
	{
		while (cur && (poly->i > cur->i
			|| (poly->i == cur->i && poly->j < cur->j)))
		{
			prec = cur;
			cur = cur->next;
		}
	}
	else if (conf->control->v->rot > 335 || conf->control->v->rot == 0)
	{
		while (cur && (poly->j < cur->j
			|| (poly->j == cur->j && poly->i > cur->i)))
		{
			prec = cur;
			cur = cur->next;
		}
	}
	poly->next = cur;
	if (prec)
		prec->next = poly;
	else
		conf->pls = poly;
}
