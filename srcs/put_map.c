/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:15:57 by mbaron            #+#    #+#             */
/*   Updated: 2018/03/02 09:38:07 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_map_img(t_conf *conf, int blind)
{
	if (blind)
		put_polygones(conf);
	else
		put_vectors(conf);
}

void		put_map(t_conf *conf)
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
	else
		ft_memcpy(c->v, c->n, sizeof(t_values));
	set_colors(conf);
	put_map_img(conf, c->v->blind);
}
