/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:19:14 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/27 18:11:24 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	matrix_change_orig(t_conf *conf, int hor, int add)
{
	double x;
	double y;

	if (!hor)
	{
		x = (add ? -1.0 : 1.0) / (double)conf->control->v->zoom;
		y = 0;
	}
	else
	{
		x = (add ? 1.0 : -1.0) / (double)conf->control->v->zoom;
		y = (add ? -1.0 : 1.0) / (double)conf->control->v->zoom * M_SQRT2;
	}
	conf->matrix[1][0] += (conf->matrix[0][3] * x + conf->matrix[0][2] * y);
	conf->matrix[1][3] += (conf->matrix[0][1] * x + conf->matrix[0][0] * y);
	conf->control->n->x = conf->matrix[1][0];
	conf->control->n->y = conf->matrix[1][3];
}

void	matrix_change_xy(t_conf *conf, int xm, int ym)
{
	double x;
	double y;

	y = ((double)(ym - conf->mouse->y)
		/ (double)conf->control->v->zoom / conf->control->v->scale
		* M_SQRT2);
	x = ((double)(conf->mouse->x - xm) + (double)(conf->mouse->y - ym))
		/ (double)conf->control->v->zoom / conf->control->v->scale;
	conf->matrix[1][0] += conf->matrix[0][3] * x + conf->matrix[0][2] * y;
	conf->matrix[1][3] += conf->matrix[0][1] * x + conf->matrix[0][0] * y;
	conf->control->n->x = conf->matrix[1][0];
	conf->control->n->y = conf->matrix[1][3];
	render(conf);
}

void	matrix_change_rot(t_conf *conf, int add)
{
	double		rot;
	double		cosr;
	double		sinr;

	conf->control->n->rot = (conf->control->v->rot + (add ? 1 : -1));
	if (conf->control->n->rot > 359)
		conf->control->n->rot = 0;
	else if (conf->control->n->rot < 0)
		conf->control->n->rot = 359;
	rot = deg2rad(conf->control->n->rot);
	cosr = cos(rot);
	sinr = sin(rot);
	conf->matrix[0][0] = cosr;
	conf->matrix[0][1] = -sinr;
	conf->matrix[0][2] = sinr;
	conf->matrix[0][3] = cosr;
}

int	value_add(t_conf *conf, int i)
{
	if (i < 2)
		matrix_change_orig(conf, i, 1);
	else if (i == 2)
		conf->control->n->z = conf->control->v->z + 1;
	else if (i == 3)
		matrix_change_rot(conf, 1);
	else if (i == 4)
		conf->control->n->zoom = conf->control->v->zoom + 1;
	else if (i == 5 && conf->control->v->proj < 1)
		conf->control->n->proj = conf->control->v->proj + 1;
	else if (i == 6 && !conf->control->v->col)
		conf->control->n->col = 1;
	else if (i == 7 && conf->control->v->floor < 0xFFFFFE)
		conf->control->n->col = conf->control->v->floor + 1;
	else if (i == 8 && conf->control->v->ceil < 0xFFFFFE)
		conf->control->n->col = conf->control->v->ceil + 1;
	render(conf);
	return (0);
}

int	value_sub(t_conf *conf, int i)
{
	if (i < 2)
		matrix_change_orig(conf, i, 0);
	else if (i == 2)
		conf->control->n->z = conf->control->v->z - 1;
	else if (i == 3)
		matrix_change_rot(conf, 0);
	else if (i == 4 && conf->control->v->zoom > 1)
		conf->control->n->zoom = conf->control->v->zoom - 1;
	else if (i == 5 && conf->control->v->proj > 1)
		conf->control->n->proj = conf->control->v->proj - 1;
	else if (i == 6 && conf->control->v->col)
		conf->control->n->col = 0;
	else if (i == 7 && conf->control->v->floor > 0x1)
		conf->control->n->col = conf->control->v->floor - 1;
	else if (i == 8 && conf->control->v->ceil > 0x1)
		conf->control->n->col = conf->control->v->ceil - 1;
	render(conf);
	return (0);
}

void	mouse_change_rot(t_conf *conf, int xm, int ym)
{
	if (ym >= (FDF_MAP_Y) + FDF_MARGE + (FDF_MAP_H) / 2.0)
	{
		if (xm > conf->mouse->x)
			value_add(conf, 3);
		else if (xm < conf->mouse->x)
			value_sub(conf, 3);
	}
	else
	{
		if (xm > conf->mouse->x)
			value_sub(conf, 3);
		else if (xm < conf->mouse->x)
			value_add(conf, 3);
	}
}

int		hook_close(t_conf *conf)
{
	(void)conf;
	exit(EXIT_SUCCESS);
	return (0);
}

int		hook_keydown(int key, t_conf *conf)
{
	conf->keypressed = key;
	return (0);
}

int		hook_keyup(int key, t_conf *conf)
{
	int		i;

	(void)key;
	if (conf->keypressed == KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	i = -1;
	while (++i < conf->control->nb)
	{
		if (conf->keypressed == conf->control->p[i]->kup
			|| conf->keypressed == conf->control->p[i]->kdn)
		{
			if (!conf->control->n)
				conf->control->n = (t_values *)init_pointer(sizeof(t_values),
				"Malloc error in hook_key (conf->control->n)");
			ft_memcpy(conf->control->n, conf->control->v, sizeof(t_values));
			if (conf->keypressed == conf->control->p[i]->kup)
				value_add(conf, i);
			else
				value_sub(conf, i);
			conf->keypressed = 0;
			return (0);
		}
	}
	conf->keypressed = 0;
	return (0);
}

void		mouse_init(t_mouse *mouse)
{
	mouse->button = 0;
	mouse->x = -1;
	mouse->y = -1;
}

void	mouse_set(t_mouse *mouse, int button, int x, int y)
{
	mouse->button = button;
	mouse->x = x;
	mouse->y = y;
}

int		hook_mousedown(int button, int x, int y, t_conf *conf)
{
	mouse_set(conf->mouse, button, x, y);
	int		i;
	int		top;

	if (button == 1 && ((x > FDF_CL_C1_X && x < FDF_CL_C1_X + FDF_CL_C_W)
		|| (x > FDF_CL_C2_X && x < FDF_CL_C2_X + FDF_CL_C_W)))
	{
		top = FDF_CL_Y + FDF_CL_H + FDF_CL_MARGE;
		i = -1;
		while (++i < conf->control->nb)
		{
			if (y > top && y < top + FDF_CL_C_H)
			{
				if (!conf->control->n)
					conf->control->n =
						(t_values *)init_pointer(sizeof(t_values),
						"Malloc error in hook_key (conf->control->n)");
				ft_memcpy(conf->control->n, conf->control->v,
					sizeof(t_values));
				if (x > FDF_CL_C1_X && x < FDF_CL_C1_X + FDF_CL_C_W)
					value_sub(conf, i);
				else
					value_add(conf, i);
				mouse_init(conf->mouse);
				return (0);
			}
			top += FDF_CL_H;
		}
	}
	return (0);
}

int		hook_mouseup(int button, int x, int y, t_conf *conf)
{
	(void)button;
	(void)x;
	(void)y;
	mouse_init(conf->mouse);
	return (0);
}

int		hook_mousemove(int xm, int ym, t_conf *conf)
{
	if ((conf->mouse->button == 1 || conf->mouse->button == 2)
		&& (conf->mouse->x != xm || conf->mouse->y != ym)
		&& xm > (FDF_MAP_X) + FDF_MARGE && xm < (FDF_MAP_X) + (FDF_MAP_W)
		&& ym > (FDF_MAP_Y) + FDF_MARGE && ym < (FDF_MAP_Y) + (FDF_MAP_H))
	{
		if (!conf->control->n)
		{
			conf->control->n =
				(t_values *)init_pointer(sizeof(t_values),
				"Malloc error in hook_key (conf->control->n)");
		}
		ft_memcpy(conf->control->n, conf->control->v, sizeof(t_values));
		if (conf->mouse->button == 1)
		{
			matrix_change_xy(conf, xm, ym);
			mouse_set(conf->mouse, 1, xm, ym);
		}
		else
		{
			mouse_change_rot(conf, xm, ym);
			mouse_set(conf->mouse, 2, xm, ym);
		}
	}
	return (0);
}
