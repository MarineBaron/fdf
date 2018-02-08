/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:15:57 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/08 07:57:55 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_img_clear(t_conf *conf)
{
	int		i;
	int		j;

	fill_rect(conf, conf->map->rect);
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < conf->control[i]->p_nb)
			fill_rect(conf, conf->control[i]->params[j]->pos_value);
	}
}

void	set_img_map(t_conf *conf)
{
	fill_rect(conf, conf->map->rect);
}
