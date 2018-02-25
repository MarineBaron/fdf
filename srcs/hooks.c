/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:19:14 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/16 18:40:31 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	value_add(t_conf *conf, int i)
{
	int		val;

	val = *(conf->control[i]->value);
	if (i == 3)
		render(conf, i, (val + 1) % 360);
	else if (val < conf->control[i]->max - 1)
		render(conf, i, val + 1);
	return (0);
}

int	value_sub(t_conf *conf, int i)
{
	int		val;

	val = *(conf->control[i]->value);
	if (i == 3)
		render(conf, i, (val - 1) % 360);
	else if (val > conf->control[i]->min + 1)
		render(conf, i, val - 1);
	return (0);
}

int		hook_key(int key, t_conf *conf)
{
	int		i;
	int		j;
	int		new;

	ft_putstr("key pressed : ");
	ft_putnbr(key);
	ft_putendl("");
	if (key == KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	i = -1;
	while (++i < conf->control->nb)
	{
		if (key == conf->control[i]->kup)
			return (value_add(conf, i));
		if (key == conf->control[i]->kdn)
			return (value_sub(conf, i));
	}
	return (0);
}

int		hook_mouse(int button, int x, int y, t_conf *conf)
{
	int		i;
	int		top;

	ft_putstr("mouse button : ");
	ft_putnbr(button);
	ft_putstr("x : ");
	ft_putnbr(x);
	ft_putstr("y : ");
	ft_putnbr(y);
	ft_putendl("");
	if (button == 1)
	{
		if ((x > FDF_CL_C1_X && x < FDF_CL_C1_X + FDF_CL_C_W)
			|| (x > FDF_CL_C2_X && x < FDF_CL_C2_X + FDF_CL_C_W))
		{
			y = FDF_CL_Y + FDF_CL_H + FDF_CL_MARGE;
			i = -1;
			while (++i < conf->control->nb)
			{
				if (y > top && y < top + FDF_CL_C_H)
				{
					if (x > FDF_CL_C1_X && x < FDF_CL_C1_X + FDF_CL_C_W)
						return (value_add(conf, i));
					else
						return (value_sub(conf, i));
				}
				y += FDF_CL_H;
			}
		}
	}
	return (0);
}
