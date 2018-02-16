/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 17:59:37 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/15 15:37:28 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

static void	config_set_params_pos_v(t_rect *rect, int y)
{
	rect = (t_rect *)init_pointer(sizeof(t_rect),
		"Error malloc in config_set_params_pos (pos_v)");
	rect->x = FDF_CL_V_X;
	rect->y = y;
	rect->w = 2 * FDF_CL_C_W;
	rect->h = FDF_CL_C_H;
	rect->c_bg = FDF_CL_BG_COLOR;
	rect->c_bd = FDF_CL_BD_COLOR;
}

static void	config_set_params_pos_button(t_rect *rect, int y, int i)
{
	rect = (t_rect *)init_pointer(sizeof(t_rect),
		"Error malloc in config_set_params_pos (buttons[i])");
	rect->x = i ? FDF_CL_C2_X : FDF_CL_C1_X;
	rect->y = y;
	rect->w = FDF_CL_C_W;
	rect->h = FDF_CL_C_H;
	rect->c_bg = FDF_CL_BTN1_COLOR;
	rect->c_bd = FDF_CL_BD_COLOR;
}

void		config_set_params(t_conf *conf, t_param **ps)
{
	int		y;
	int		i;
	int		j;

	i = -1;
	while (++i < conf->control->nb)
	{
		ps[i] = (t_param *)init_pointer(sizeof(t_param),
		"Error malloc in config_default (params[i])");
		y = FDF_CL_X + (i + 1) * FDF_CL_H + FDF_CL_MARGE;
		config_set_params_pos_v(ps[i]->pos_v, i);
		ps[i]->buttons = (t_rect **)init_pointer(
			2 * sizeof(t_rect *),
			"Error malloc in config_set_params_pos (buttons)");
		j = -1;
		while (++j < 2)
			config_set_params_pos_button(ps[i]->buttons[j], y, j);
	}
	config_set_params_name(ps);
	config_set_params_value(conf->control, ps);
	config_set_params_minmax(ps);
	config_set_params_keys(ps);
}
