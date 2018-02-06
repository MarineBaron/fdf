/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:13:51 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/06 15:36:14 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_control	*mlx_control_init_pointers(const char *title, int nb)
{
	t_control	*cc;

	cc = NULL;
	if (!(cc = (t_control *)malloc(sizeof(t_control))))
		set_error("Malloc Echec in mlx_control_get_world (cc)", 1);
	cc->p_nb = nb;
	if (!(cc->title = ft_strdup(title)))
		set_error("Malloc Echec in mlx_control_get_world (title)", 1);
	if (!(cc->p_name = (char **)malloc(nb * sizeof(char *))))
		set_error("Malloc Echec in mlx_control_get_world (p_name)", 1);
	if (!(cc->p_value = (char **)malloc(nb * sizeof(char *))))
		set_error("Malloc Echec in mlx_control_get_world (p_value)", 1);
	if (!(cc->p_min = (int *)malloc(nb * sizeof(int))))
		set_error("Malloc Echec in mlx_control_get_world (p_min)", 1);
	if (!(cc->p_max = (int *)malloc(nb * sizeof(int))))
		set_error("Malloc Echec in mlx_control_get_world (p_max)", 1);
	return (cc);
}

static void	mlx_control_set_param(t_control *cc, int index, const char *p_name,
	int p_value)
{
	if (!(cc->p_name[index] = ft_strdup(p_name)))
		set_error("Malloc Echec in mlx_control_set_params (p_name)", 1);
	if (!(cc->p_value[index] = ft_itoa(p_value)))
		set_error("Malloc Echec in mlx_control_set_params (p_value)", 1);
}

static void	mlx_control_set_minmax(t_control *cc, int index, int min, int max)
{
	cc->p_min[index] = min;
	cc->p_min[index] = max;
}

static void	mlx_control_put_init(t_rect *rect, t_rect *button)
{
	rect->x = FDF_CONTROL_X;
	rect->w = FDF_CONTROL_W;
	rect->h = FDF_CONTROL_H;
	rect->c_bg = FDF_CONTROL_BG_COLOR;
	rect->c_bd = FDF_CONTROL_BD_COLOR;
	button->w = FDF_CONTROL_C_W;
	button->h = FDF_CONTROL_C_H;
	button->c_bg = FDF_CONTROL_BUTTON1_COLOR;
	button->c_bd = FDF_CONTROL_BD_COLOR;
}

static void	mlx_control_put_param(t_conf *conf, int y,
	t_rect *rect, t_rect *button)
{
	rect->y = y;
	fill_rect(conf, rect);
	button->x = FDF_CONTROL_C1_X;
	button->y = y + FDF_CONTROL_MARGE;
	fill_rect(conf, button);
	button->x = FDF_CONTROL_C2_X;
	fill_rect(conf, button);
}

static void	mlx_control_put_param_color(t_conf *conf, t_rect *button, int color)
{
	button->x = FDF_CONTROL_V_X;
	button->c_bg = color;
	fill_rect(conf, button);
	button->c_bg = FDF_CONTROL_BUTTON1_COLOR;
}

void	mlx_control_put_txt(t_conf *conf)
{
	int		i;
	int		j;
	int		y;

	y = FDF_MARGE;
	i = -1;
	while (++i < 3)
	{
		mlx_string_put(conf->mlx, conf->win, FDF_CONTROL_P_X, y,
			FDF_CONTROL_TXT2_COLOR, conf->control[i]->title);
		y += FDF_CONTROL_H;
		j = -1;
		while (++j < conf->control[i]->p_nb)
		{
			mlx_string_put(conf->mlx, conf->win, FDF_CONTROL_P_X, y,
				FDF_CONTROL_TXT1_COLOR, conf->control[i]->p_name[j]);
			if (!(i == 2 && (j > 1)))
				mlx_string_put(conf->mlx, conf->win, FDF_CONTROL_V_X, y,
					FDF_CONTROL_TXT2_COLOR, conf->control[i]->p_value[j]);
			mlx_string_put(conf->mlx, conf->win,
				FDF_CONTROL_C1_X + FDF_CONTROL_C_DEC, y,
				FDF_CONTROL_TXT2_COLOR, "-");
			mlx_string_put(conf->mlx, conf->win,
				FDF_CONTROL_C2_X + FDF_CONTROL_C_DEC, y,
				FDF_CONTROL_TXT2_COLOR, "+");
			y += FDF_CONTROL_H;
		}
	}
}

static void	mlx_control_put_img(t_conf *conf)
{
	t_rect	*rect;
	t_rect	*button;
	int		i;
	int		j;
	int		y;

	if (!(rect = (t_rect *)malloc(sizeof(t_rect))))
		set_error("Malloc Echec in mlx_control_put (rect)", 1);
	if (!(button = (t_rect *)malloc(sizeof(t_rect))))
		set_error("Malloc Echec in mlx_control_put (button)", 1);
	mlx_control_put_init(rect, button);
	y = FDF_MARGE;
	i = -1;
	while (++i < 3)
	{
		y += FDF_CONTROL_H;
		j = -1;
		while (++j < conf->control[i]->p_nb)
		{
			mlx_control_put_param(conf, y, rect, button);
			if (i == 2 && j > 1)
				mlx_control_put_param_color(conf, button, (j % 2)
					? conf->color->ceil : conf->color->floor);
			y += FDF_CONTROL_H;
		}
	}
	ft_memdel((void **)&rect);
	ft_memdel((void **)&button);
}

static void	mlx_control_get_world(t_conf *conf)
{
	t_control	*cc;

	cc = mlx_control_init_pointers("WORLD", FDF_PARAM_NB_WORLD);
	mlx_control_set_param(cc, 0, "Center X (%)", conf->world->x);
	mlx_control_set_param(cc, 1, "Center Y (%)", conf->world->y);
	mlx_control_set_param(cc, 2, "Center Z (%)", conf->world->z);
	mlx_control_set_param(cc, 3, "Zoom (%)", conf->world->zoom);
	mlx_control_set_param(cc, 4, "Rotate (deg)", conf->world->rot);
	mlx_control_set_minmax(cc, 0, FDF_MIN_WORLD_X, FDF_MAX_WORLD_X);
	mlx_control_set_minmax(cc, 1, FDF_MIN_WORLD_Y, FDF_MAX_WORLD_Y);
	mlx_control_set_minmax(cc, 2, FDF_MIN_WORLD_Z, FDF_MAX_WORLD_Z);
	mlx_control_set_minmax(cc, 3, FDF_MIN_WORLD_ZOOM, FDF_MAX_WORLD_ZOOM);
	mlx_control_set_minmax(cc, 4, FDF_MIN_WORLD_ROT, FDF_MAX_WORLD_ROT);
	conf->control[0] = cc;
}

static void	mlx_control_get_camera(t_conf *conf)
{
	t_control	*cc;

	cc = mlx_control_init_pointers("CAMERA", FDF_PARAM_NB_CAMERA);
	mlx_control_set_param(cc, 0, "Position X", conf->camera->x);
	mlx_control_set_param(cc, 1, "Position Y", conf->camera->y);
	mlx_control_set_param(cc, 2, "Position Z", conf->camera->z);
	mlx_control_set_param(cc, 3, "Rotate on X axis (deg)", conf->camera->rx);
	mlx_control_set_param(cc, 4, "Rotate on Y axis (deg)", conf->camera->ry);
	mlx_control_set_param(cc, 5, "Rotate on Z axis (deg)", conf->camera->rz);
	mlx_control_set_minmax(cc, 0, FDF_MIN_CAM_X, FDF_MAX_CAM_X);
	mlx_control_set_minmax(cc, 1, FDF_MIN_CAM_Y, FDF_MAX_CAM_Y);
	mlx_control_set_minmax(cc, 2, FDF_MIN_CAM_Z, FDF_MAX_CAM_Z);
	mlx_control_set_minmax(cc, 3, FDF_MIN_CAM_RX, FDF_MAX_CAM_RX);
	mlx_control_set_minmax(cc, 4, FDF_MIN_CAM_RY, FDF_MAX_CAM_RY);
	mlx_control_set_minmax(cc, 5, FDF_MIN_CAM_RZ, FDF_MAX_CAM_RZ);
	conf->control[1] = cc;
}

static void	mlx_control_get_proj(t_conf *conf)
{
	t_control	*cc;

	cc = mlx_control_init_pointers("PROECTION & COLORS", FDF_PARAM_NB_PROJ);
	mlx_control_set_param(cc, 0, "1 = parall, 2 = iso, 3 = ???",
		conf->proj->val);
	mlx_control_set_param(cc, 1, "Color gradient (0/1)", conf->proj->col);
	mlx_control_set_param(cc, 2, "Floor's color", conf->color->floor);
	mlx_control_set_param(cc, 3, "Ceil's color", conf->color->ceil);
	mlx_control_set_minmax(cc, 0, FDF_MIN_PROJ_VAL, FDF_MAX_PROJ_VAL);
	mlx_control_set_minmax(cc, 1, FDF_MIN_PROJ_COL, FDF_MAX_PROJ_COL);
	mlx_control_set_minmax(cc, 2, FDF_MIN_PROJ_COLF, FDF_MAX_PROJ_COLF);
	mlx_control_set_minmax(cc, 3, FDF_MIN_PROJ_COLC, FDF_MAX_PROJ_COLC);
	conf->control[2] = cc;
}

void	mlx_control(t_conf *conf)
{
	mlx_control_get_world(conf);
	mlx_control_get_camera(conf);
	mlx_control_get_proj(conf);
	mlx_control_put_img(conf);
}
