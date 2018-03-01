/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:19:14 by mbaron            #+#    #+#             */
/*   Updated: 2018/03/01 08:49:28 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		value_add(t_conf *conf, int i)
{
	if (i < 2)
		matrix_change_orig(conf, i, 1);
	else if (i == 2)
		conf->control->n->z = conf->control->v->z + 1;
	else if (i == 3)
		matrix_change_rot(conf, 1);
	else if (i == 4)
		conf->control->n->zoom = conf->control->v->zoom + 1;
	else if (i == 5 && conf->control->v->proj < 1)
		conf->control->n->proj = conf->control->v->proj + 1;
	else if (i == 6 && !conf->control->v->blind)
		conf->control->n->blind = 1;
	else if (i == 7 && !conf->control->v->col)
		conf->control->n->col = 1;
	else if (i == 8 && conf->control->v->floor < 0xFFFFFE)
		conf->control->n->col = conf->control->v->floor + 1;
	else if (i == 9 && conf->control->v->ceil < 0xFFFFFE)
		conf->control->n->col = conf->control->v->ceil + 1;
	render(conf);
	return (0);
}

int		value_sub(t_conf *conf, int i)
{
	if (i < 2)
		matrix_change_orig(conf, i, 0);
	else if (i == 2)
		conf->control->n->z = conf->control->v->z - 1;
	else if (i == 3)
		matrix_change_rot(conf, 0);
	else if (i == 4 && conf->control->v->zoom > 1)
		conf->control->n->zoom = conf->control->v->zoom - 1;
	else if (i == 5 && conf->control->v->proj > 1)
		conf->control->n->proj = conf->control->v->proj - 1;
	else if (i == 6 && conf->control->v->blind)
		conf->control->n->blind = 0;
	else if (i == 7 && conf->control->v->col)
		conf->control->n->col = 0;
	else if (i == 8 && conf->control->v->floor > 0x1)
		conf->control->n->col = conf->control->v->floor - 1;
	else if (i == 9 && conf->control->v->ceil > 0x1)
		conf->control->n->col = conf->control->v->ceil - 1;
	render(conf);
	return (0);
}

void	mouse_change_rot(t_conf *conf, int xm, int ym)
{
	if (ym >= (FDF_MAP_Y) + FDF_MARGE + (FDF_MAP_H) / 2.0)
	{
		if (xm > conf->mouse->x)
			value_add(conf, 3);
		else if (xm < conf->mouse->x)
			value_sub(conf, 3);
	}
	else
	{
		if (xm > conf->mouse->x)
			value_sub(conf, 3);
		else if (xm < conf->mouse->x)
			value_add(conf, 3);
	}
}
