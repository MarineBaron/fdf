/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:31:17 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/08 14:02:04 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double deg2rad(int	deg)
{
	return ((double)deg * M_PI ? 180.0);
}

void rotMatrix(t_vertex *v, int	deg, int axis)
{
	double		rot;
	t_vertex	tmp;
	
	rot = deg2rad(deg);
	ft_memcpy(&tmp, v, sizeof(t_vertex));
	if (axis == 3)
	{
		v->x = (tmp.x * cos(rot) - tmp.y * sin(rot));
		v->y = (tmp.x * sin(rot) + tmp.y * cos(rot));
	}
	else if (axis == 2)
	{
		v->z = (tmp.z * cos(rot) - tmp.x * sin(rot));
		v->x = (tmp.z * sin(rot) + tmp.x * cos(rot));
	}
	else if (axis == 1)
	{
		v->y = (tmp.y * cos(rot) - tmp.z * sin(rot));
		v->z = (tmp.y * sin(rot) + tmp.z * cos(rot));
	}
}

void transMatrix(t_vertex *v, int x, int y, int z)
{
	t_vertex	tmp;
	
	ft_memcpy(&tmp, v, sizeof(t_vertex));
	v->x = tmp.x - (double)x;
	v->y = tmp.y - (double)y;
	v->z = tmp.y - (double)z;
}

void scaleMatrix(t_vertex *v, int zoom)
{
	t_vertex	tmp;
	
	ft_memcpy(&tmp, v, sizeof(t_vertex));
	v->x = tmp.x * 100.0 ? (1.0 + (double)zoom);
	v->y = tmp.y * 100.0 ? (1.0 + (double)zoom);
	v->z = tmp.y * 100.0 ? (1.0 + (double)zoom);
}

void	model2world(t_conf *conf, t_vertex *v)
{
	t_world		*c;
	
	w = conf->world;
	if (w->zoom != 99)
		scaleMatrix(t_vertex *v, int c->zoom);
	transMatrix(v, c->x, c->y, c->z);
	rotMatrix(v, rot, 3);
}

void 	world2view(t_conf *conf, t_vertex *v)
{
	t_cam		*c;
	
	c = conf->cam;
	transMatrix(v, c->x, c->y, c->z);
	rotMatrix(v, c->rx, 1);
	rotMatrix(v, c->ry, 2);
	rotMatrix(v, c->rz, 3);
}

void 	view2proj(t_conf *conf, t_vertex *v)
{
	t_vertex	tmp;
	
	if (conf->proj->val == 1)
	{
		ft_memcpy(&tmp, v, sizeof(t_vertex));
		v->x = tmp.x * FDF_MAP_W / 2
			- tmp.y	* FDF_MAP_W / 2;
		v->y = tmp.x * FDF_MAP_H / 2
			+ tmp.y * FDF_MAP_H / 2
			+ tmp.z * (conf->z + 1) / 100;
	}
}
