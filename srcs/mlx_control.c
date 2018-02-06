/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:13:51 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/06 19:52:45 by mbaron           ###   ########.fr       */
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
	if (!(cc->p_value = (int*)malloc(nb * sizeof(int))))
		set_error("Malloc Echec in mlx_control_get_world (p_value)", 1);
	if (!(cc->p_min = (int *)malloc(nb * sizeof(int))))
		set_error("Malloc Echec in mlx_control_get_world (p_min)", 1);
	if (!(cc->p_max = (int *)malloc(nb * sizeof(int))))
		set_error("Malloc Echec in mlx_control_get_world (p_max)", 1);
	if (!(cc->k_up = (int *)malloc(nb * sizeof(int))))
		set_error("Malloc Echec in mlx_control_get_world (p_kup)", 1);
	if (!(cc->k_dwn = (int *)malloc(nb * sizeof(int))))
		set_error("Malloc Echec in mlx_control_get_world (p_kdn)", 1);
	if (!(cc->buttons = (t_rect ***)malloc(nb * sizeof(t_rect **))))
		set_error("Malloc Echec in mlx_control_get_world (buttons)", 1);
	if (!(cc->buttons[0] = (t_rect **)malloc(sizeof(t_rect *))))
		set_error("Malloc Echec in mlx_control_get_world (buttons[0])", 1);
	if (!(cc->buttons[1] = (t_rect **)malloc(sizeof(t_rect *))))
		set_error("Malloc Echec in mlx_control_get_world (buttons[1])", 1);
	return (cc);
}

static void	mlx_control_set_param(t_control *cc, int index, const char *p_name,
	int p_value)
{
	if (!(cc->p_name[index] = ft_strdup(p_name)))
		set_error("Malloc Echec in mlx_control_set_params (p_name)", 1);
	cc->p_value[index] = p_value;
}

static void	mlx_control_set_minmax(t_control *cc, int index, int min, int max)
{
	cc->p_min[index] = min;
	cc->p_min[index] = max;
}

static void	mlx_control_set_keys(t_control *cc, int index, int k_up, int k_dwn)
{
	cc->k_up[index] = k_up;
	cc->k_dwn[index] = k_dwn;
}

static void	mlx_control_put_init(t_rect *rect, t_rect **buttons)
{
	rect->x = FDF_CONTROL_X;
	rect->w = FDF_CONTROL_W;
	rect->h = FDF_CONTROL_H;
	rect->c_bg = FDF_CONTROL_BG_COLOR;
	rect->c_bd = FDF_CONTROL_BD_COLOR;
	buttons[0]->w = FDF_CONTROL_C_W;
	buttons[0]->h = FDF_CONTROL_C_H;
	buttons[0]->c_bg = FDF_CONTROL_BUTTON1_COLOR;
	buttons[0]->c_bd = FDF_CONTROL_BD_COLOR;
	buttons[1]->w = FDF_CONTROL_C_W;
	buttons[1]->h = FDF_CONTROL_C_H;
	buttons[1]->c_bg = FDF_CONTROL_BUTTON1_COLOR;
	buttons[1]->c_bd = FDF_CONTROL_BD_COLOR;
}

static t_rect	**mlx_control_put_param(t_conf *conf, int y)
{
	t_rect	**buttons;
	t_rect	*rect;

	if (!(rect = (t_rect *)malloc(sizeof(t_rect))))
		set_error("Malloc Echec in mlx_control_put (rect)", 1);
	if (!(buttons = (t_rect **)malloc(2 * sizeof(t_rect *))))
		set_error("Malloc Echec in mlx_control_get_world (buttons)", 1);
	if (!(buttons[0] = (t_rect *)malloc(sizeof(t_rect))))
		set_error("Malloc Echec in mlx_control_put_param (buttons[0])", 1);
	if (!(buttons[1] = (t_rect *)malloc(sizeof(t_rect))))
		set_error("Malloc Echec in mlx_control_put_param (buttons[1])", 1);
	mlx_control_put_init(rect, buttons);
	rect->y = y;
	fill_rect(conf, rect);
	buttons[0]->x = FDF_CONTROL_C1_X;
	buttons[0]->y = y + FDF_CONTROL_MARGE;
	fill_rect(conf, buttons[0]);
	buttons[1]->x = FDF_CONTROL_C2_X;
	buttons[1]->y = buttons[0]->y;
	fill_rect(conf, buttons[1]);
	return (buttons);
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
					FDF_CONTROL_TXT2_COLOR,
					ft_itoa(conf->control[i]->p_value[j]));
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
	t_rect	**buttons;
	int		i;
	int		j;
	int		y;

	y = FDF_MARGE;
	i = -1;
	while (++i < 3)
	{
		y += FDF_CONTROL_H;
		j = -1;
		while (++j < conf->control[i]->p_nb)
		{
			buttons = mlx_control_put_param(conf, y);
			conf->control[i]->buttons[j] = buttons;
			if (i == 2 && j > 1)
				mlx_control_put_param_color(conf, buttons[1], (j % 2)
					? conf->color->ceil : conf->color->floor);
			// ft_memdel((void **)&buttons[0]);
			// ft_memdel((void **)&buttons[1]);
			// ft_memdel((void **)&buttons);
			buttons = NULL;
			y += FDF_CONTROL_H;
		}
	}
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
	mlx_control_set_keys(cc, 0, FDF_KUP_WORLD_X, FDF_KDN_WORLD_X);
	mlx_control_set_keys(cc, 1, FDF_KUP_WORLD_Y, FDF_KDN_WORLD_Y);
	mlx_control_set_keys(cc, 2, FDF_KUP_WORLD_Z, FDF_KDN_WORLD_Z);
	mlx_control_set_keys(cc, 3, FDF_KUP_WORLD_ZOOM, FDF_KDN_WORLD_ZOOM);
	mlx_control_set_keys(cc, 4, FDF_KUP_WORLD_ROT, FDF_KDN_WORLD_ROT);
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
	mlx_control_set_keys(cc, 0, FDF_KUP_CAM_X, FDF_KDN_CAM_X);
	mlx_control_set_keys(cc, 1, FDF_KUP_CAM_Y, FDF_KDN_CAM_Y);
	mlx_control_set_keys(cc, 2, FDF_KUP_CAM_Z, FDF_KDN_CAM_Z);
	mlx_control_set_keys(cc, 3, FDF_KUP_CAM_RX, FDF_KDN_CAM_RX);
	mlx_control_set_keys(cc, 4, FDF_KUP_CAM_RY, FDF_KDN_CAM_RY);
	mlx_control_set_keys(cc, 5, FDF_KUP_CAM_RZ, FDF_KDN_CAM_RZ);
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
	mlx_control_set_keys(cc, 0, FDF_KUP_PROJ_VAL, FDF_KDN_PROJ_VAL);
	mlx_control_set_keys(cc, 1, FDF_KUP_PROJ_COL, FDF_KDN_PROJ_COL);
	mlx_control_set_keys(cc, 2, FDF_KUP_PROJ_COLF, FDF_KDN_PROJ_COLF);
	mlx_control_set_keys(cc, 3, FDF_KUP_PROJ_COLC, FDF_KDN_PROJ_COLC);
	conf->control[2] = cc;
}

void	mlx_control(t_conf *conf)
{
	mlx_control_get_world(conf);
	mlx_control_get_camera(conf);
	mlx_control_get_proj(conf);
	mlx_control_put_img(conf);
}
