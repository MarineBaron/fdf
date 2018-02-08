/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 17:59:37 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/07 19:41:52 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

static t_world	*config_default_world(void)
{
	t_world	*world;

	world = (t_world *)init_pointer(sizeof(t_world),
		"Error malloc in config_default_world");
	world->zoom = FDF_W_ZOOM;
	world->x = FDF_W_X;
	world->y = FDF_W_Y;
	world->z = FDF_W_Z;
	world->rot = FDF_W_ROT;
	return (world);
}

static t_cam	*config_default_cam(void)
{
	t_cam	*cam;

	cam = (t_cam *)init_pointer(sizeof(t_cam),
		"Error malloc in config_default_cam");
	cam->x = FDF_C_X;
	cam->y = FDF_C_Y;
	cam->z = FDF_C_Z;
	cam->rx = FDF_C_RX;
	cam->ry = FDF_C_RY;
	cam->rz = FDF_C_RZ;
	return (cam);
}

static t_colc	*config_default_color(void)
{
	t_colc	*col;

	col = (t_colc *)init_pointer(sizeof(t_colc),
		"Error malloc in config_default_color");
	col->floor = (t_col)FDF_COL_FLOOR;
	col->ceil = (t_col)FDF_COL_CEIL;
	return (col);
}

t_conf			*config_default(void)
{
	t_conf	*conf;

	conf = (t_conf *)init_pointer(sizeof(t_conf),
		"Error malloc in config_default (conf)");
	conf->world = config_default_world();
	conf->camera = config_default_cam();
	conf->color = config_default_color();
	conf->proj = (t_proj *)init_pointer(sizeof(t_proj),
		"Error malloc in config_default (proj)");
	conf->proj->val = FDF_P_VAL;
	conf->proj->col = FDF_P_COL;
	return (conf);
}
