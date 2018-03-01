/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_geom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 12:14:47 by mbaron            #+#    #+#             */
/*   Updated: 2018/03/01 10:39:25 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double			deg2rad(int deg)
{
	return ((double)deg * M_PI / 180.0);
}

t_rect			*get_rect(int x, int y, int w, int h)
{
	t_rect	*rect;

	rect = (t_rect *)init_pointer(NULL, sizeof(t_rect), "ErrM in get_rect");
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return (rect);
}

void			fill_rect(t_img *img, t_rect *rect)
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

static t_vtxi	*trans_vtx(t_vtx *v)
{
	t_vtxi	*vi;

	vi = (t_vtxi *)init_pointer(NULL, sizeof(t_vtxi), "ErrM (vtxi)");
	vi->c = v->c;
	vi->x = (int)floor(v->x + 0.5);
	vi->y = (int)floor(v->y + 0.5);
	return (vi);
}

t_vector		*set_vector(t_vtx *v1, t_vtx *v2)
{
	t_vector	*v;
	t_vtxi		*vi1;
	t_vtxi		*vi2;

	vi1 = trans_vtx(v1);
	vi2 = trans_vtx(v2);
	v = (t_vector *)init_pointer(NULL, sizeof(t_vector), "ErrM (vector)");
	if (vi1->x == vi2->x)
	{
		v->o = (vi2->y < vi1->y) ? vi2 : vi1;
		v->d = (vi2->y < vi1->y) ? vi1 : vi2;
	}
	else
	{
		v->o = (vi2->x < vi1->x) ? vi2 : vi1;
		v->d = (vi2->x < vi1->x) ? vi1 : vi2;
	}
	return (v);
}
