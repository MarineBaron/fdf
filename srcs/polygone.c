/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:27:46 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/28 20:21:27 by mbaron           ###   ########.fr       */
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
	poly->minx = -DBL_MAX;
	poly->minx = fmax(poly->minx, conf->mapt->vtx[i][j]->x);
	poly->minx = fmax(poly->minx, conf->mapt->vtx[i + 1][j]->x);
	poly->minx = fmax(poly->minx, conf->mapt->vtx[i + 1][j - 1]->x);
	poly->minx = fmax(poly->minx, conf->mapt->vtx[i][j - 1]->x);
	poly->miny = -DBL_MAX;
	poly->miny = fmax(poly->miny, conf->mapt->vtx[i][j]->y);
	poly->miny = fmax(poly->miny, conf->mapt->vtx[i + 1][j]->y);
	poly->miny = fmax(poly->miny, conf->mapt->vtx[i + 1][j - 1]->y);
	poly->miny = fmax(poly->miny, conf->mapt->vtx[i][j - 1]->y);
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
	while (cur && (poly->miny > cur->miny
			|| (poly->miny == cur->miny && poly->minx < cur->minx)))
	{
		prec = cur;
		cur = cur->next;
	}
	poly->next = cur;
	if (prec)
		prec->next = poly;
	else
		conf->pls = poly;
}