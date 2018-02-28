/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_geom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 12:14:47 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/28 20:03:13 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double		deg2rad(int deg)
{
	return ((double)deg * M_PI / 180.0);
}

t_rect		*get_rect(int x, int y, int w, int h)
{
	t_rect	*rect;

	rect = (t_rect *)init_pointer(NULL, sizeof(t_rect), "ErrM in get_rect");
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return (rect);
}

void		fill_rect(t_img *img, t_rect *rect)
{
	int		i;
	int		j;
	char	*ptr;

	ptr = img->ptr;
	i = -1;
	while (++i < rect->h)
	{
		ptr = img->ptr + (((rect->y + i) * img->sl) + rect->x * img->bpp);
		j = -1;
		while (++j < rect->w)
		{
			ft_memcpy(ptr, (void *)&rect->c_bg, img->bpp);
			ptr += img->bpp;
		}
	}
}

t_vector	*set_vector(t_vtx *v1, t_vtx *v2)
{
	t_vector	*v;

	v = (t_vector *)init_pointer(NULL, sizeof(t_vector), "ErrM (verctor)");
	if (v1->x == v2->x)
	{
		v->o = (v2->y < v1->y) ? v2 : v1;
		v->d = (v2->y < v1->y) ? v1 : v2;
	}
	else
	{
		v->o = (v2->x < v1->x) ? v2 : v1;
		v->d = (v2->x < v1->x) ? v1 : v2;
	}
	return (v);
}
