/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:15:57 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/17 09:29:23 by mbaron           ###   ########.fr       */
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

void			set_img_map(t_conf *conf, int index, int new)
{
	int			i;
	int			j;
	t_vertex	*v;

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
	set_img_map_vectors(conf);
}
