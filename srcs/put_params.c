/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 18:15:54 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/16 17:31:56 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		put_control_values(t_conf *conf)
{
	int		i;
	int		y;
	t_rect	*rect;

	i = -1;
	y = FDF_CL_Y + FDF_CL_H + FDF_CL_MARGE;
	while (++i < conf->control->nb - 2)
	{
		mlx_string_put(conf->mlx, conf->win,
			FDF_CL_V_X, y, FDF_CL_TXT2_COLOR,
			ft_itoa(*(conf->control[i]->value)));
		y += FDF_CL_H;
	}
	rect = get_rect(0, 0, conf->i_btn->w, conf->i_btn->h);
	rect->c_bg = conf->control->floor;
	fill_rect(conf->i_btn, rect);
	mlx_put_image_to_window(conf->mlx, conf->win, conf->i_btn->img,
		FDF_CL_V_X, y);
	y += FDF_CL_H;
	rect->c_bg = conf->control->ceil;
	fill_rect(conf->i_btn, rect);
	mlx_put_image_to_window(conf->mlx, conf->win, conf->i_btn->img,
		FDF_CL_V_X, y);
}
