/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 09:23:07 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/01 11:02:24 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# define DIR_EXE ..
# define DIR_CONFIG DIR_EXE/config
# define DIR_MAPS DIR_EXE/maps
# define CONFIG_FILE_DEFAULT config.def.text
# define MAP_FILE_DEFAULT 42.fdf

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
typedef struct	s_conf
{
	t_world	wor;
	t_cam	cam;
	t_proj	pro;
}				t_conf;
int				config_init(int argc, char *argv[], t_mapi *mapi, t_conf *conf);
#endif
