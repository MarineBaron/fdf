/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_control_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 18:15:54 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/28 19:56:34 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*get_value(t_conf *conf, int i)
{
	t_control *c;

	c = conf->control;
	if (i == 0)
		return (ft_itoa(floor((c->n ? c->n->x : c->v->x) + 0.5)));
	if (i == 1)
		return (ft_itoa(floor((c->n ? c->n->y : c->v->y) + 0.5)));
	if (i == 2)
		return (ft_itoa(c->n ? c->n->z : c->v->z));
	if (i == 3)
		return (ft_itoa(c->n ? c->n->rot : c->v->rot));
	if (i == 4)
		return (ft_itoa(c->n ? c->n->zoom : c->v->zoom));
	if (i == 5)
		return (ft_itoa(c->n ? c->n->proj : c->v->proj));
	if (i == 6)
		return (ft_itoa(c->n ? c->n->col : c->v->col));
	return ("");
}

static void	put_control_buttons(t_conf *conf, int y)
{
	t_rect	*rect;

	rect = get_rect(0, 0, conf->i_btn->w, conf->i_btn->h);
	rect->c_bg = conf->control->v->floor;
	fill_rect(conf->i_btn, rect);
	mlx_put_image_to_window(conf->mlx, conf->win, conf->i_btn->img,
		FDF_CL_V_X, y);
	y += FDF_CL_H;
	rect->c_bg = conf->control->v->ceil;
	fill_rect(conf->i_btn, rect);
	mlx_put_image_to_window(conf->mlx, conf->win, conf->i_btn->img,
		FDF_CL_V_X, y);
	ft_memdel((void **)rect);
}

void		put_control_values(t_conf *conf)
{
	int		i;
	int		y;
	char	*value;

	i = -1;
	y = FDF_CL_Y + FDF_CL_H + FDF_CL_MARGE;
	while (++i < conf->control->nb - 2)
	{
		if (!(value = get_value(conf, i)))
			set_error(conf, "Error(ft_itoa)", 1);
		mlx_string_put(conf->mlx, conf->win,
			FDF_CL_V_X, y, FDF_CL_TXT2_COLOR, value);
		y += FDF_CL_H;
		ft_memdel((void **)&value);
	}
	put_control_buttons(conf, y);
}
