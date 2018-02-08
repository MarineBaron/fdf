/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:13:51 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/08 08:24:13 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		set_txt_control_value(t_conf *conf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < conf->control[i]->p_nb)
		{
			if (!(i == 2 && j > 1))
				mlx_string_put(conf->mlx, conf->win,
					conf->control[i]->params[j]->pos_value->x + FDF_CL_MARGE,
					conf->control[i]->params[j]->pos_value->y + FDF_CL_MARGE,
					FDF_CL_TXT1_COLOR,
					ft_itoa(*(conf->control[i]->params[j]->value)));
		}
	}
}

void		set_txt_control(t_conf *conf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		mlx_string_put(conf->mlx, conf->win,
			conf->control[i]->pos_title->x + FDF_CL_MARGE,
			conf->control[i]->pos_title->y + FDF_CL_MARGE,
			FDF_CL_TXT2_COLOR, conf->control[i]->title);
		j = -1;
		while (++j < conf->control[i]->p_nb)
		{
			mlx_string_put(conf->mlx, conf->win,
				conf->control[i]->params[j]->pos_param->x + FDF_CL_MARGE,
				conf->control[i]->params[j]->pos_param->y + FDF_CL_MARGE,
				FDF_CL_TXT1_COLOR, conf->control[i]->params[j]->name);
		}
	}
}

static void	set_img_button(t_conf *conf, t_rect **buttons)
{
	int		l;
	int		i;
	int		j;
	char	*ptr;
	int		col;

	col = FDF_CL_TXT2_COLOR;
	l = buttons[0]->w / 4;
	i = -1;
	while (++i < 2)
	{
		j = l;
		ptr = conf->ptr + (buttons[i]->y + 2 * l) * conf->sl
			+ buttons[i]->x * conf->bpp;
		while (++j < 3 * l)
			ft_memcpy(ptr + j * conf->bpp, &col, conf->bpp);
		if (i & 1)
		{
			j = l;
			ptr = conf->ptr + buttons[i]->y * conf->sl
				+ (buttons[i]->x + 2 * l) * conf->bpp;
			while (++j < 3 * l)
				ft_memcpy(ptr + j * conf->sl, &col, conf->bpp);
		}
	}
}

void		set_img_control_value(t_conf *conf)
{
	int		j;

	j = 1;
	while (++j < conf->control[2]->p_nb)
	{
		conf->control[2]->params[j]->pos_value->c_bg = (j == 2)
			? conf->color->floor : conf->color->ceil;
		fill_rect(conf, conf->control[2]->params[j]->pos_value);
	}
}

void		set_img_control(t_conf *conf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		fill_rect(conf, conf->control[i]->pos_title);
		j = -1;
		while (++j < conf->control[i]->p_nb)
		{
			fill_rect(conf, conf->control[i]->params[j]->pos_param);
			fill_rect(conf, conf->control[i]->params[j]->buttons[0]);
			fill_rect(conf, conf->control[i]->params[j]->buttons[1]);
			set_img_button(conf, conf->control[i]->params[j]->buttons);
		}
	}
}
