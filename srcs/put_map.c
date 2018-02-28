/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:15:57 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/28 20:41:12 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			put_map(t_conf *conf)
{
	t_control *c;

	c = conf->control;
	if (!c->n)
	{
		conf->matrix = matrix_init(conf, c->v);
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
	put_vectors(conf);
	//put_polygones(conf);
}
