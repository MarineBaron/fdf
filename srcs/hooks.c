/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:19:14 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/08 09:18:00 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		hook_key(int key, t_conf *conf)
{
	int		i;
	int		j;

	ft_putstr("key pressed : ");
	ft_putnbr(key);
	ft_putendl("");
	if (key == KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < conf->control[i]->p_nb)
		{
			if (key == conf->control[i]->params[j]->kup
				&& *(conf->control[i]->params[j]->value)
				< conf->control[i]->params[j]->max - 1)
			{
				ft_putstr("add : ");
				ft_putendl(conf->control[i]->params[j]->name);
				*(conf->control[i]->params[j]->value) += 1;
				render(conf);
				return (0);
			}
			if (key == conf->control[i]->params[j]->kdwn
				&& *(conf->control[i]->params[j]->value)
				> conf->control[i]->params[j]->min)
			{
				ft_putstr("sub : ");
				ft_putendl(conf->control[i]->params[j]->name);
				*(conf->control[i]->params[j]->value) -= 1;
				render(conf);
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

	ft_putstr("mouse button : ");
	ft_putnbr(button);
	ft_putstr("x : ");
	ft_putnbr(x);
	ft_putstr("y : ");
	ft_putnbr(y);
	ft_putendl("");
	if (button == 1)
	{
		i = -1;
		while (++i < 3)
		{
			j = -1;
			while (++j < conf->control[i]->p_nb)
			{
				if (is_inrect(conf->control[i]->params[j]->buttons[1], x, y)
					&& *(conf->control[i]->params[j]->value)
					< conf->control[i]->params[j]->max - 1)
				{
					ft_putstr("add : ");
					ft_putendl(conf->control[i]->params[j]->name);
					*(conf->control[i]->params[j]->value) += 1;
					render(conf);
					return (0);
				}
				if (is_inrect(conf->control[i]->params[j]->buttons[0], x, y)
					&& *(conf->control[i]->params[j]->value)
					> conf->control[i]->params[j]->min)
				{
					ft_putstr("sub : ");
					ft_putendl(conf->control[i]->params[j]->name);
					*(conf->control[i]->params[j]->value) -= 1;
					render(conf);
					return (0);
				}
			}
		}
	}
	return (0);
}
