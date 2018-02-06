/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:15:57 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/06 15:08:32 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_map(t_conf *conf)
{
	t_rect	*rect;

	if (!(rect = (t_rect *)malloc(sizeof(t_rect))))
		set_error("Malloc Echec in mlx_control_put (rect)", 1);
	rect->x = FDF_MAP_X;
	rect->y = FDF_MAP_Y;
	rect->w = FDF_MAP_W;
	rect->h = FDF_MAP_H;
	rect->c_bg = FDF_MAP_BG_COLOR;
	rect->c_bd = FDF_MAP_BD_COLOR;
	fill_rect(conf, rect);
	ft_memdel((void **)&rect);
}
