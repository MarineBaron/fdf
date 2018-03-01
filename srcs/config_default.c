/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 17:59:37 by mbaron            #+#    #+#             */
/*   Updated: 2018/03/01 09:12:55 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

static void	config_set_params_pos_v(t_rect *rect, int y)
{
	rect = get_rect((FDF_CL_V_X), y, 2 * (FDF_CL_C_W), (FDF_CL_C_H));
	rect->c_bg = FDF_CL_BG_COLOR;
	rect->c_bd = FDF_CL_BD_COLOR;
}

static void	config_set_params_pos_button(t_rect *rect, int y, int i)
{
	rect = get_rect(i ? (FDF_CL_C2_X) : (FDF_CL_C1_X), y,
		2 * (FDF_CL_C_W), (FDF_CL_C_H));
	rect->c_bg = FDF_CL_BTN1_COLOR;
	rect->c_bd = FDF_CL_BD_COLOR;
}

static void	config_set_params_name(t_conf *conf, t_param **ps)
{
	if (!(ps[0]->name = ft_strdup(FDF_T_X)))
		set_error(conf, "ErrM (params name)", 1);
	if (!(ps[1]->name = ft_strdup(FDF_T_Y)))
		set_error(conf, "ErrM (params name)", 1);
	if (!(ps[2]->name = ft_strdup(FDF_T_Z)))
		set_error(conf, "ErrM (params name)", 1);
	if (!(ps[3]->name = ft_strdup(FDF_T_R)))
		set_error(conf, "ErrM (params name)", 1);
	if (!(ps[4]->name = ft_strdup(FDF_T_O)))
		set_error(conf, "ErrM (params name)", 1);
	if (!(ps[5]->name = ft_strdup(FDF_T_P)))
		set_error(conf, "ErrM (params name)", 1);
	if (!(ps[6]->name = ft_strdup(FDF_T_B)))
		set_error(conf, "ErrM (params name)", 1);
	if (!(ps[7]->name = ft_strdup(FDF_T_G)))
		set_error(conf, "ErrM (params name)", 1);
	if (!(ps[8]->name = ft_strdup(FDF_T_F)))
		set_error(conf, "ErrM (params name)", 1);
	if (!(ps[9]->name = ft_strdup(FDF_T_C)))
		set_error(conf, "ErrM (params name)", 1);
}

static void	config_set_params_keys(t_param **ps)
{
	ps[0]->kdn = FDF_KDN_X;
	ps[0]->kup = FDF_KUP_X;
	ps[1]->kdn = FDF_KDN_Y;
	ps[1]->kup = FDF_KUP_Y;
	ps[2]->kdn = FDF_KDN_Z;
	ps[2]->kup = FDF_KUP_Z;
	ps[3]->kdn = FDF_KDN_R;
	ps[3]->kup = FDF_KUP_R;
	ps[4]->kdn = FDF_KDN_O;
	ps[4]->kup = FDF_KUP_O;
	ps[5]->kdn = FDF_KDN_P;
	ps[5]->kup = FDF_KUP_P;
	ps[6]->kdn = FDF_KDN_B;
	ps[6]->kup = FDF_KUP_B;
	ps[7]->kdn = FDF_KDN_G;
	ps[7]->kup = FDF_KUP_G;
	ps[8]->kdn = FDF_KDN_F;
	ps[8]->kup = FDF_KUP_F;
	ps[9]->kdn = FDF_KDN_C;
	ps[9]->kup = FDF_KUP_C;
}

void		config_set_params(t_conf *conf, t_param **ps)
{
	int		y;
	int		i;
	int		j;

	i = -1;
	while (++i < conf->control->nb)
	{
		ps[i] = (t_param *)init_pointer(conf, sizeof(t_param),
			"ErrM (params[i])");
		y = FDF_CL_X + (i + 1) * FDF_CL_H + FDF_CL_MARGE;
		config_set_params_pos_v(ps[i]->pos_v, i);
		ps[i]->buttons = (t_rect **)init_pointer(conf, 2 * sizeof(t_rect *),
			"ErrM (buttons)");
		j = -1;
		while (++j < 2)
			config_set_params_pos_button(ps[i]->buttons[j], y, j);
	}
	config_set_params_name(conf, ps);
	config_set_params_keys(ps);
}
