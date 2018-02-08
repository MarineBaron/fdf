/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 08:33:34 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/08 08:42:25 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

void		config_control_set_world(t_conf *conf)
{
	t_control	*cc;

	cc = config_control_init_pointers(FDF_PM_TITLE_W, FDF_PM_NB_W);
	config_control_set_param(cc->params[0], FDF_PM_W_0, &(conf->world->x));
	config_control_set_param(cc->params[1], FDF_PM_W_1, &(conf->world->y));
	config_control_set_param(cc->params[2], FDF_PM_W_2, &(conf->world->z));
	config_control_set_param(cc->params[3], FDF_PM_W_3, &(conf->world->zoom));
	config_control_set_param(cc->params[4], FDF_PM_W_4, &(conf->world->rot));
	config_control_set_minmax(cc->params[0], FDF_MIN_W_X, FDF_MAX_W_X);
	config_control_set_minmax(cc->params[1], FDF_MIN_W_Y, FDF_MAX_W_Y);
	config_control_set_minmax(cc->params[2], FDF_MIN_W_Z, FDF_MAX_W_Z);
	config_control_set_minmax(cc->params[3], FDF_MIN_W_ZOOM, FDF_MAX_W_ZOOM);
	config_control_set_minmax(cc->params[4], FDF_MIN_W_ROT, FDF_MAX_W_ROT);
	config_control_set_keys(cc->params[0], FDF_KUP_W_X, FDF_KDN_W_X);
	config_control_set_keys(cc->params[1], FDF_KUP_W_Y, FDF_KDN_W_Y);
	config_control_set_keys(cc->params[2], FDF_KUP_W_Z, FDF_KDN_W_Z);
	config_control_set_keys(cc->params[3], FDF_KUP_W_ZOOM, FDF_KDN_W_ZOOM);
	config_control_set_keys(cc->params[4], FDF_KUP_W_ROT, FDF_KDN_W_ROT);
	conf->control[0] = cc;
}

void		config_control_set_camera(t_conf *conf)
{
	t_control	*cc;

	cc = config_control_init_pointers(FDF_PM_TITLE_C, FDF_PM_NB_C);
	config_control_set_param(cc->params[0], FDF_PM_C_0, &(conf->camera->x));
	config_control_set_param(cc->params[1], FDF_PM_C_1, &(conf->camera->y));
	config_control_set_param(cc->params[2], FDF_PM_C_2, &(conf->camera->z));
	config_control_set_param(cc->params[3], FDF_PM_C_3, &(conf->camera->rx));
	config_control_set_param(cc->params[4], FDF_PM_C_4, &(conf->camera->ry));
	config_control_set_param(cc->params[5], FDF_PM_C_5, &(conf->camera->rz));
	config_control_set_minmax(cc->params[0], FDF_MIN_C_X, FDF_MAX_C_X);
	config_control_set_minmax(cc->params[1], FDF_MIN_C_Y, FDF_MAX_C_Y);
	config_control_set_minmax(cc->params[2], FDF_MIN_C_Z, FDF_MAX_C_Z);
	config_control_set_minmax(cc->params[3], FDF_MIN_C_RX, FDF_MAX_C_RX);
	config_control_set_minmax(cc->params[4], FDF_MIN_C_RY, FDF_MAX_C_RY);
	config_control_set_minmax(cc->params[5], FDF_MIN_C_RZ, FDF_MAX_C_RZ);
	config_control_set_keys(cc->params[0], FDF_KUP_C_X, FDF_KDN_C_X);
	config_control_set_keys(cc->params[1], FDF_KUP_C_Y, FDF_KDN_C_Y);
	config_control_set_keys(cc->params[2], FDF_KUP_C_Z, FDF_KDN_C_Z);
	config_control_set_keys(cc->params[3], FDF_KUP_C_RX, FDF_KDN_C_RX);
	config_control_set_keys(cc->params[4], FDF_KUP_C_RY, FDF_KDN_C_RY);
	config_control_set_keys(cc->params[5], FDF_KUP_C_RZ, FDF_KDN_C_RZ);
	conf->control[1] = cc;
}

void		config_control_set_proj(t_conf *conf)
{
	t_control	*cc;

	cc = config_control_init_pointers(FDF_PM_TITLE_P, FDF_PM_NB_P);
	config_control_set_param(cc->params[0], FDF_PM_P_0, &(conf->proj->val));
	config_control_set_param(cc->params[1], FDF_PM_P_1, &(conf->proj->col));
	config_control_set_param(cc->params[2], FDF_PM_P_2,
		(int *)&(conf->color->floor));
	config_control_set_param(cc->params[3], FDF_PM_P_3,
		(int *)&(conf->color->ceil));
	config_control_set_minmax(cc->params[0], FDF_MIN_P_VAL, FDF_MAX_P_VAL);
	config_control_set_minmax(cc->params[1], FDF_MIN_P_COL, FDF_MAX_P_COL);
	config_control_set_minmax(cc->params[2], FDF_MIN_P_COLF, FDF_MAX_P_COLF);
	config_control_set_minmax(cc->params[3], FDF_MIN_P_COLC, FDF_MAX_P_COLC);
	config_control_set_keys(cc->params[0], FDF_KUP_P_VAL, FDF_KDN_P_VAL);
	config_control_set_keys(cc->params[1], FDF_KUP_P_COL, FDF_KDN_P_COL);
	config_control_set_keys(cc->params[2], FDF_KUP_P_COLF, FDF_KDN_P_COLF);
	config_control_set_keys(cc->params[3], FDF_KUP_P_COLC, FDF_KDN_P_COLC);
	conf->control[2] = cc;
}

static void	config_control_set_pos_param(t_param *param, t_rect *rect,
	t_rect *button)
{
	rect->x = FDF_CL_P_X;
	rect->c_bg = FDF_CL_BG_COLOR;
	ft_memcpy(param->pos_param, rect, sizeof(t_rect));
	button->x = FDF_CL_V_X;
	button->c_bg = FDF_CL_BG_COLOR;
	ft_memcpy(param->pos_value, button, sizeof(t_rect));
	button->c_bg = FDF_CL_BTN1_COLOR;
	button->x = FDF_CL_C1_X;
	ft_memcpy(param->buttons[0], button, sizeof(t_rect));
	button->x = FDF_CL_C2_X;
	ft_memcpy(param->buttons[1], button, sizeof(t_rect));
}

void		config_control_set_pos(t_conf *conf)
{
	t_rect	rect;
	t_rect	button;
	int		i;
	int		j;

	config_control_init_pos(&rect, &button);
	i = -1;
	while (++i < 3)
	{
		rect.x = FDF_CL_P_X;
		rect.c_bg = FDF_WIN_BG_COLOR;
		ft_memcpy(conf->control[i]->pos_title, &rect, sizeof(t_rect));
		rect.y += FDF_CL_H;
		button.y += FDF_CL_H;
		j = -1;
		while (++j < conf->control[i]->p_nb)
		{
			config_control_set_pos_param(conf->control[i]->params[j], &rect,
				&button);
			rect.y += FDF_CL_H;
			button.y += FDF_CL_H;
		}
	}
}
