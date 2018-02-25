/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:13:51 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/15 15:30:51 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
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
					conf->control[i][j]->pos_value->x + FDF_CL_MARGE,
					conf->control[i][j]->pos_value->y + FDF_CL_MARGE,
					FDF_CL_TXT1_COLOR,
					ft_itoa(*(conf->control[i][j]->value)));
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
				conf->control[i][j]->pos_param->x + FDF_CL_MARGE,
				conf->control[i][j]->pos_param->y + FDF_CL_MARGE,
				FDF_CL_TXT1_COLOR, conf->control[i][j]->name);
		}
	}
}

static void	set_img_button(t_conf *conf, t_button **buttons)
{
	int		w;
	int		h;

	buttons[0]->img = mlx_xpm_file_to_image(conf->mlx,
		"./buttons/minus.xpm", &w, &h);
	buttons[1]->img = mlx_xpm_file_to_image(conf->mlx,
		"./buttons/plus.xpm", &w, &h);
}

void		set_buttons_imgs(t_conf *conf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < conf->control[i]->p_nb)
		{
			if ()
			mlx_put_image_to_window(conf->mlx, conf->win, conf->control[i][j]->buttons[0]->img, conf->control[i][j]->buttons[0]->rect->x, conf->control[i][j]->buttons[0]->rect->y);
			mlx_put_image_to_window(conf->mlx, conf->win, conf->control[i][j]->buttons[1]->img, conf->control[i][j]->buttons[1]->rect->x, conf->control[i][j]->buttons[1]->rect->y);
		}
	}
	
	
}

void		set_img_control_value(t_conf *conf)
{
	int		j;

	j = 1;
	while (++j < conf->control[2]->p_nb)
	{
		conf->control[2][j]->pos_value->c_bg = (j == 2)
			? conf->color->floor : conf->color->ceil;
		fill_rect(conf, conf->control[2][j]->pos_value);
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
			fill_rect(conf, conf->control[i][j]->pos_param);
			fill_rect(conf, conf->control[i][j]->buttons[0]->rect);
			fill_rect(conf, conf->control[i][j]->buttons[1]->rect);
			set_img_button(conf, conf->control[i][j]->buttons);
		}
	}
}
*/
