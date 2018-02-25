/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 12:29:12 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/17 10:24:18 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	config_set_params_value(t_control *c, t_param **ps)
{
	ps[0]->value = &(c->v->x);
	ps[1]->value = &(c->v->y);
	ps[2]->value = &(c->v->z);
	ps[3]->value = &(c->v->rot);
	ps[4]->value = &(c->v->zoom);
	ps[5]->value = &(c->v->proj);
	ps[6]->value = &(c->v->col);
	ps[7]->value = &(c->v->floor);
	ps[8]->value = &(c->v->ceil);
}

void	config_set_params_name(t_param **ps)
{
	if (!(ps[0]->name = ft_strdup(FDF_T_X)))
		set_error("Malloc error in config_set_params_name", 1);
	if (!(ps[1]->name = ft_strdup(FDF_T_Y)))
		set_error("Malloc error in config_set_params_name", 1);
	if (!(ps[2]->name = ft_strdup(FDF_T_Z)))
		set_error("Malloc error in config_set_params_name", 1);
	if (!(ps[3]->name = ft_strdup(FDF_T_R)))
		set_error("Malloc error in config_set_params_name", 1);
	if (!(ps[4]->name = ft_strdup(FDF_T_O)))
		set_error("Malloc error in config_set_params_name", 1);
	if (!(ps[5]->name = ft_strdup(FDF_T_P)))
		set_error("Malloc error in config_set_params_name", 1);
	if (!(ps[6]->name = ft_strdup(FDF_T_G)))
		set_error("Malloc error in config_set_params_name", 1);
	if (!(ps[7]->name = ft_strdup(FDF_T_F)))
		set_error("Malloc error in config_set_params_name", 1);
	if (!(ps[8]->name = ft_strdup(FDF_T_C)))
		set_error("Malloc error in config_set_params_name", 1);
}

void	config_set_params_minmax(t_param **ps)
{
	ps[0]->min = FDF_MIN_X;
	ps[0]->max = FDF_MAX_X;
	ps[1]->min = FDF_MIN_Y;
	ps[1]->max = FDF_MAX_Y;
	ps[2]->min = FDF_MIN_Z;
	ps[2]->max = FDF_MAX_Z;
	ps[3]->min = FDF_MIN_R;
	ps[3]->max = FDF_MAX_R;
	ps[4]->min = FDF_MIN_O;
	ps[4]->max = FDF_MAX_O;
	ps[5]->min = FDF_MIN_P;
	ps[5]->max = FDF_MAX_P;
	ps[6]->min = FDF_MIN_G;
	ps[6]->max = FDF_MAX_G;
	ps[7]->min = FDF_MIN_F;
	ps[7]->max = FDF_MAX_F;
	ps[8]->min = FDF_MIN_C;
	ps[8]->max = FDF_MAX_C;
}

void	config_set_params_keys(t_param **ps)
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
	ps[6]->kdn = FDF_KDN_G;
	ps[6]->kup = FDF_KUP_G;
	ps[7]->kdn = FDF_KDN_F;
	ps[7]->kup = FDF_KUP_F;
	ps[8]->kdn = FDF_KDN_C;
	ps[8]->kup = FDF_KUP_C;
}
