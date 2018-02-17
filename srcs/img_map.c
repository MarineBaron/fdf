/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:15:57 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/16 18:48:34 by mbaron           ###   ########.fr       */
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
	t_colc		*col;
	int			r;
	int			g;
	int			b;

	col = conf->color;
	if (z == conf->mapi->hmin)
		return (col->floor);
	if (z == conf->mapi->hmax)
		return (col->ceil);
	p = (z - conf->mapi->hmin) / (conf->mapi->hmax - conf->mapi->hmin);
	r = get_grad_col(col->floor >> 16, col->ceil >> 16, p);
	b = get_grad_col((col->floor >> 8) & 0xFF, (col->ceil >> 8) & 0xFF, p);
	g = get_grad_col(col->floor & 0xFF, col->ceil & 0xFF, p);
	return ((r << 16) | (b << 8) | g);
}

void			set_img_map(t_conf *conf)
{
	int			i;
	int			j;
	t_vertex	*v;
	t_vector	*vector;

	
	i = -1;
	while (++i < conf->mapi->h)
	{
		j = -1;
		while (++j < conf->mapi->w)
		{
			v = conf->map->vertexes[i][j];
			ft_memcpy(v, conf->mapi->vertexes[i][j], sizeof(t_vertex));
			model2view(conf, v);
			if (conf->control->col)
				v->c = map_get_color_gradient(conf, v->z);
			view2proj(conf, v);
		}
	}
	set_img_map_vectors(conf, vector);
}
