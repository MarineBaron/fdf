/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 18:45:30 by mbaron            #+#    #+#             */
/*   Updated: 2018/03/01 19:07:15 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_pixel(t_conf *conf, int x, int y, t_vector *v)
{
	unsigned int	c;
	double			p;

	if (x <= FDF_MAP_W && y <= FDF_MAP_H)
	{
		if (v->o->x == v->d->x && v->o->y == v->d->y)
			c = v->o->c;
		else
		{
			p = (abs(v->o->x - v->d->x) > abs(v->o->y - v->d->y))
				? ((double)(x - v->o->x) / (double)(v->d->x - v->o->x))
				: ((double)(y - v->o->y) / (double)(v->d->y - v->o->y));
			c = (get_grad_col((v->o->c >> 16), (v->d->c >> 16), p) << 16)
				^ (get_grad_col((v->o->c >> 8) & 0xFF,
					(v->d->c >> 8) & 0xFF, p) << 8)
				^ get_grad_col(v->o->c & 0xFF, v->d->c & 0xFF, p);
			if (!conf->control->v->blind)
				ft_memcpy(conf->i_map->ptr + conf->i_map->sl * y
					+ conf->i_map->bpp * x, &c, conf->i_map->bpp);
			else if (y < conf->i_map->maxy[x])
			{
				conf->i_map->tmp_maxy[x] = y;
				ft_memcpy(conf->i_map->ptr + conf->i_map->sl * y
					+ conf->i_map->bpp * x, &c, conf->i_map->bpp);
			}
		}
	}
}

static void	put_line_hor(t_conf *conf, t_vector *v, int dx, int dy)
{
	int		x;
	int		y;
	int		p;
	int		c;
	int		i;

	x = v->o->x;
	y = v->o->y;
	p = (dy > 0) ? 1 : -1;
	dy = abs(dy);
	put_pixel(conf, x, y, v);
	c = dx / 2;
	i = 0;
	while (++i <= dx)
	{
		x++;
		c += dy;
		if (c >= dx)
		{
			c -= dx;
			y += p;
		}
		put_pixel(conf, x, y, v);
	}
}

static void	put_line_ver(t_conf *conf, t_vector *v, int dx, int dy)
{
	int		x;
	int		y;
	int		p;
	int		c;
	int		i;

	x = v->o->x;
	y = v->o->y;
	p = (dy > 0) ? 1 : -1;
	dy = abs(dy);
	put_pixel(conf, x, y, v);
	c = dy / 2;
	i = 0;
	while (++i <= dy)
	{
		y += p;
		c += dx;
		if (c >= dy)
		{
			c -= dy;
			x++;
		}
		put_pixel(conf, x, y, v);
	}
}

static void	put_line_simple(t_conf *conf, t_vector *v, int dx, int dy)
{
	int		x;
	int		y;

	if (!dx)
	{
		if (!dy)
		{
			put_pixel(conf, v->o->x, v->o->y, v);
			return ;
		}
		y = v->o->y - 1;
		while (++y <= v->d->y)
			put_pixel(conf, v->o->x, y, v);
		return ;
	}
	if (!dy)
	{
		x = v->o->x - 1;
		while (++x <= v->d->x)
			put_pixel(conf, x, v->o->y, v);
		return ;
	}
}

void		put_line(t_conf *conf, t_vtx *v1, t_vtx *v2)
{
	int			dx;
	int			dy;
	t_vector	*v;

	v = set_vector(v1, v2);
	dx = v->d->x - v->o->x;
	dy = v->d->y - v->o->y;
	if (!dx || !dy)
	{
		put_line_simple(conf, v, dx, dy);
		return ;
	}
	if (dx > abs(dy))
		put_line_hor(conf, v, dx, dy);
	else
		put_line_ver(conf, v, dx, dy);
	ft_memdel((void **)&v->o);
	ft_memdel((void **)&v->d);
	ft_memdel((void **)&v);
}
