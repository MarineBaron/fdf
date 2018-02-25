/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_control_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 09:25:34 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/14 12:43:16 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_param	*config_control_init_param(void)
{
	t_param *param;

	param = (t_param *)init_pointer(sizeof(t_param),
		"Malloc Echec (cc[i]->pos_param)");
	param->pos_param = (t_rect *)init_pointer(sizeof(t_rect),
		"Malloc Echec (cc[i]->pos_param)");
	param->pos_value = (t_rect *)init_pointer(sizeof(t_rect),
		"Malloc Echec (cc[i]->pos_value)");
		/*
	param->buttons = (t_rect **)init_pointer(2 * sizeof(t_rect *),
			"Malloc Echec (cc[i]->buttons[0])");
	param->buttons[0] = (t_rect *)init_pointer(sizeof(t_rect),
		"Malloc Echec (cc[i]->buttons[0])");
	param->buttons[1] = (t_rect *)init_pointer(sizeof(t_rect),
		"Malloc Echec (cc[i]->buttons[1])");
		*/
		param->buttons = (t_button **)init_pointer(2 * sizeof(t_button *),
				"Malloc Echec (cc[i]->buttons)");
		param->buttons[0] = (t_button *)init_pointer(sizeof(t_button),
			"Malloc Echec (cc[i]->buttons[0])");
		param->buttons[1] = (t_button *)init_pointer(sizeof(t_button),
			"Malloc Echec (cc[i]->buttons[1])");
		param->buttons[0]->rect = (t_rect *)init_pointer(sizeof(t_rect),
			"Malloc Echec (cc[i]->buttons[0])");
		param->buttons[1]->rect = (t_rect *)init_pointer(sizeof(t_rect),
			"Malloc Echec (cc[i]->buttons[1])");
	return (param);
}

t_control		*config_control_init_pointers(const char *title, int nb)
{
	t_control	*cc;
	int			i;

	cc = (t_control *)init_pointer(sizeof(t_control), "Malloc Echec (cc)");
	cc->p_nb = nb;
	cc->title = NULL;
	if (!(cc->title = ft_strdup(title)))
		set_error("Malloc Echec (cc->title)", 1);
	cc->pos_title = (t_rect *)init_pointer(sizeof(t_rect),
		"Malloc Echec (cc->pos_title)");
	cc = (t_param **)init_pointer(nb * sizeof(t_param *),
		"Malloc Echec (cc)");
	i = -1;
	while (++i < nb)
		cc[i] = config_control_init_param();
	return (cc);
}

void			config_control_set_param(t_param *param, const char *name,
	int *p_value)
{
	if (!(param->name = ft_strdup(name)))
		set_error("Malloc Echec in mlx_control_set_params (name)", 1);
	param->value = p_value;
}

void			config_control_set_minmax(t_param *param, int min, int max)
{
	param->min = min;
	param->max = max;
}

void			config_control_set_keys(t_param *param, int kup, int kdwn)
{
	param->kup = kup;
	param->kdwn = kdwn;
}

void			config_control_init_pos(t_rect *rect, t_rect *button)
{
	rect->x = FDF_MARGE;
	rect->y = FDF_MARGE;
	rect->w = FDF_CL_W;
	rect->h = FDF_CL_H;
	rect->c_bg = FDF_CL_BG_COLOR;
	rect->c_bd = FDF_CL_BD_COLOR;
	button->y = rect->y + FDF_CL_MARGE;
	button->w = FDF_CL_C_W;
	button->h = FDF_CL_C_H;
	button->c_bd = FDF_CL_BD_COLOR;
}
