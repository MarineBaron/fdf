/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 17:59:37 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/01 18:44:52 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

static t_world	*config_default_world(void)
{
	t_world	*world;

	world = NULL;
	if (!(world = (t_world *)malloc(sizeof(t_world))))
		set_error("Error malloc in config_default_world", 1);
	world->zoom = FDF_WORLD_ZOOM;
	world->x = FDF_WORLD_X;
	world->y = FDF_WORLD_Y;
	world->z = FDF_WORLD_Z;
	return (world);
}

static t_cam	*config_default_cam(void)
{
	t_cam	*cam;

	cam = NULL;
	if (!(cam = (t_cam *)malloc(sizeof(t_cam))))
		set_error("Error malloc in config_default_cam", 1);
	cam->x = FDF_CAM_X;
	cam->y = FDF_CAM_Y;
	cam->z = FDF_CAM_Z;
	cam->rx = FDF_CAM_RX;
	cam->ry = FDF_CAM_RY;
	cam->rz = FDF_CAM_RZ;
	return (cam);
}

static t_colc	*config_default_color(void)
{
	t_col	*colf;
	t_col	*colc;
	t_colc	*col;

	col = NULL;
	if (!(col = (t_colc *)malloc(sizeof(t_colc))))
		set_error("Error malloc in config_default_color", 1);
	colf = NULL;
	if (!(colf = (t_col *)malloc(sizeof(t_col))))
		set_error("Error malloc in config_default_color", 1);
	colc = NULL;
	if (!(colc = (t_col *)malloc(sizeof(t_col))))
		set_error("Error malloc in config_default_color", 1);
	colf->r = FDF_COL_FLOOR_R;
	colf->g = FDF_COL_FLOOR_G;
	colf->b = FDF_COL_FLOOR_B;
	colc->r = FDF_COL_CEIL_R;
	colc->g = FDF_COL_CEIL_G;
	colc->b = FDF_COL_CEIL_B;
	col->floor = colf;
	col->ceil = colc;
	return (col);
}

t_conf			*config_default(t_conf *conf)
{
	t_proj	*proj;

	conf = NULL;
	if (!(conf = (t_conf *)malloc(sizeof(t_conf))))
		set_error("Error malloc in config_world", 1);
	conf->world = config_default_world();
	conf->camera = config_default_cam();
	conf->color = config_default_color();
	proj = NULL;
	if (!(proj = (t_proj *)malloc(sizeof(t_proj))))
		set_error("Error malloc in config_world", 1);
	proj->val = FDF_PROJ_VAL;
	conf->proj = proj;
	return (conf);
}
