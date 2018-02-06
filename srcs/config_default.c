/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 17:59:37 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/06 18:46:31 by mbaron           ###   ########.fr       */
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
	world->rot = FDF_WORLD_ROT;
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
	t_colc	*col;

	col = NULL;
	if (!(col = (t_colc *)malloc(sizeof(t_colc))))
		set_error("Error malloc in config_default_color", 1);
	col->floor = (t_col)FDF_COL_FLOOR;
	col->ceil = (t_col)FDF_COL_CEIL;
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
	proj->col = FDF_PROJ_COL;
	conf->proj = proj;
	return (conf);
}
