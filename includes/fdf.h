/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 09:23:07 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/01 16:22:16 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include "libft.h"

typedef	struct	s_col
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_col;
typedef	struct	s_point
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_point;
typedef struct	s_mapi
{
	int		h;
	int		w;
	t_point	**point;
}				t_mapi;
typedef	struct	s_world
{
	int		zoom;
	int		rot;
	int		x;
	int		y;
	int		z;
}				t_world;
typedef	struct	s_cam
{
	int		x;
	int		y;
	int		z;
	int		rx;
	int		ry;
	int		rz;
}				t_cam;
typedef	struct	s_proj
{
	int		val;
}				t_proj;
typedef	struct	s_colc
{
	t_col	*floor;
	t_col	*ceil;
}				t_colc;
typedef struct	s_conf
{
	t_world	*world;
	t_cam	*camera;
	t_proj	*proj;
	t_colc	*color;
	t_mapi	*mapi;
}				t_conf;
int				config_init(int argc, char *argv[], t_conf *conf);
int				set_error(char *str, int exit);
#endif
