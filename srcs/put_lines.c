/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:27:46 by mbaron            #+#    #+#             */
/*   Updated: 2018/03/02 17:21:19 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	polygones_set(t_conf *conf)
{
	int		i;
	int		j;

	conf->pls = NULL;
	i = -1;
	while (++i < conf->mapi->h - 1)
	{
		j = conf->mapi->w;
		while (--j > 0)
		{
			if (conf->mapt->vtx[i][j]->visible
				&& conf->mapt->vtx[i + 1][j]->visible
				&& conf->mapt->vtx[i + 1][j - 1]->visible
				&& conf->mapt->vtx[i][j - 1]->visible)
				polygone_insert(conf, i, j);
		}
	}
}

static void	polygones_remove(t_conf *conf)
{
	t_poly	*tmp;

	while (conf->pls->next)
	{
		tmp = conf->pls->next;
		ft_memdel((void**)&conf->pls);
		conf->pls = tmp;
	}
	ft_memdel((void**)&conf->pls);
}

void		put_polygones(t_conf *conf)
{
	t_poly	*cur;
	int		k;
	int		i;

	polygones_set(conf);
	cur = conf->pls;
	i = 0;
	while (cur)
	{
		k = -1;
		while (++k < conf->i_map->w)
			conf->i_map->tmp_maxy[k] = conf->i_map->maxy[k];
		put_line(conf, cur->vtx[0], cur->vtx[1]);
		put_line(conf, cur->vtx[1], cur->vtx[2]);
		put_line(conf, cur->vtx[2], cur->vtx[3]);
		put_line(conf, cur->vtx[3], cur->vtx[0]);
		k = -1;
		while (++k < conf->i_map->w)
			conf->i_map->maxy[k] = conf->i_map->tmp_maxy[k];
		cur = cur->next;
		i++;
	}
	polygones_remove(conf);
}

void		put_vectors(t_conf *conf)
{
	int			i;
	int			j;

	i = -1;
	while (++i < conf->mapi->h)
	{
		j = -1;
		while (++j < conf->mapi->w)
		{
			if (i > 0 && conf->mapt->vtx[i][j]->visible
				&& conf->mapt->vtx[i - 1][j]->visible)
				put_line(conf, conf->maps->vtx[i][j],
						conf->maps->vtx[i - 1][j]);
			if (j < conf->mapi->w - 1 && conf->mapt->vtx[i][j]->visible
				&& conf->mapt->vtx[i][j + 1]->visible)
				put_line(conf, conf->maps->vtx[i][j],
						conf->maps->vtx[i][j + 1]);
		}
	}
}
