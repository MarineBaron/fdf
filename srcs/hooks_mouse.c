/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 17:06:51 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/28 20:33:54 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mouse_init(t_mouse *mouse)
{
	mouse->button = 0;
	mouse->x = -1;
	mouse->y = -1;
}

void	mouse_set(t_mouse *mouse, int button, int x, int y)
{
	mouse->button = button;
	mouse->x = x;
	mouse->y = y;
}

int		hook_mousedown(int button, int x, int y, t_conf *conf)
{
	int		i;
	int		top;

	mouse_set(conf->mouse, button, x, y);
	if (button == 1 && ((x > FDF_CL_C1_X && x < FDF_CL_C1_X + FDF_CL_C_W)
		|| (x > FDF_CL_C2_X && x < FDF_CL_C2_X + FDF_CL_C_W)))
	{
		top = FDF_CL_Y + FDF_CL_H + FDF_CL_MARGE;
		i = -1;
		while (++i < conf->control->nb)
		{
			if (y > top && y < top + FDF_CL_C_H)
			{
				copy_control(conf);
				if (x > FDF_CL_C1_X && x < FDF_CL_C1_X + FDF_CL_C_W)
					value_sub(conf, i);
				else
					value_add(conf, i);
				mouse_init(conf->mouse);
				return (0);
			}
			top += FDF_CL_H;
		}
	}
	return (0);
}

int		hook_mouseup(int button, int x, int y, t_conf *conf)
{
	(void)button;
	(void)x;
	(void)y;
	mouse_init(conf->mouse);
	return (0);
}

int		hook_mousemove(int xm, int ym, t_conf *conf)
{
	if ((conf->mouse->button == 1 || conf->mouse->button == 2)
		&& (conf->mouse->x != xm || conf->mouse->y != ym)
		&& xm > (FDF_MAP_X) + FDF_MARGE && xm < (FDF_MAP_X) + (FDF_MAP_W)
		&& ym > (FDF_MAP_Y) + FDF_MARGE && ym < (FDF_MAP_Y) + (FDF_MAP_H))
	{
		copy_control(conf);
		if (conf->mouse->button == 1)
		{
			matrix_change_xy(conf, xm, ym);
			mouse_set(conf->mouse, 1, xm, ym);
		}
		else
		{
			mouse_change_rot(conf, xm, ym);
			mouse_set(conf->mouse, 2, xm, ym);
		}
	}
	return (0);
}
