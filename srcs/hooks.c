/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:19:14 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/06 19:00:19 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		hook_key(int key, t_conf *conf)
{
	int		i;
	int		j;

	if (key == KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < conf->control[i]->p_nb)
		{
			if (key == conf->control[i]->k_up[j]
				&& conf->control[i]->p_value[j] < conf->control[i]->p_max[j] - 1)
			{
				(conf->control[i]->p_value[j])++;
				return (0);
			}
			if (key == conf->control[i]->k_dwn[j]
				&& conf->control[i]->p_value[j] > conf->control[i]->p_min[j])
			{
				(conf->control[i]->p_value[j])++;
				return (0);
			}
		}
	}
	return (0);
}

static int		is_inrect(t_rect *rect, int x, int y)
{
	return (x >= rect->x && x <= rect->x + rect->w
				&& y >= rect->y && y <= rect->y + rect->h);
}

int		hook_mouse(int button, int x, int y, t_conf *conf)
{
	int		i;
	int		j;

	if (button == 1)
	{
		i = -1;
		while (++i < 3)
		{
			j = -1;
			while (++j < conf->control[i]->p_nb)
			{
				if (is_inrect(conf->control[i]->buttons[j][1], x, y)
					&& conf->control[i]->p_value[j]
					< conf->control[i]->p_max[j] - 1)
				{
					(conf->control[i]->p_value[j])++;
					return (0);
				}
				if (is_inrect(conf->control[i]->buttons[j][0], x, y)
					&& conf->control[i]->p_value[j]
					> conf->control[i]->p_min[j])
				{
					(conf->control[i]->p_value[j])++;
					return (0);
				}
			}
		}
	}
	return (0);
}
