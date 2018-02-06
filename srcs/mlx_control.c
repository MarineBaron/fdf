/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:13:51 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/06 06:53:02 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_control_c	*mlx_control_init_pointers(const char *title, int nb)
{
	t_control_c	*cc;

	cc = NULL;
	if (!(cc = (t_control_c *)malloc(sizeof(t_control_c))))
		set_error("Malloc Echec in mlx_control_get_world (cc)", 1);
	cc->p_nb = nb;
	if (!(cc->title = ft_strdup(title)))
		set_error("Malloc Echec in mlx_control_get_world (title)", 1);
	if (!(cc->p_name = (char **)malloc(nb * sizeof(char *))))
		set_error("Malloc Echec in mlx_control_get_world (p_name)", 1);
	if (!(cc->p_value = (char **)malloc(nb * sizeof(char *))))
		set_error("Malloc Echec in mlx_control_get_world (p_value)", 1);
	if (!(cc->i_value = (t_rect *)malloc(nb * sizeof(t_rect))))
		set_error("Malloc Echec in mlx_control_get_world (values)", 1);
	if (!(cc->i_control = (t_rect *)malloc(2 * nb * sizeof(t_rect))))
		set_error("Malloc Echec in mlx_control_get_world (p_name)", 1);
	return (cc);
}

static void	mlx_control_set_param(t_control_c *cc, int index, const char *p_name, int p_value)
{
	if (!(cc->p_name[index] = ft_strdup(p_name)))
		set_error("Malloc Echec in mlx_control_set_params (p_name)", 1);
	if (!(cc->p_value[index] = ft_itoa(p_value)))
		set_error("Malloc Echec in mlx_control_set_params (p_value)", 1);
}

static void fill_rect(t_conf *conf, t_rect	*rect)
{
	int		i;
	int		j;
	char	*ptr;

	ptr = conf->ptr;
	i = -1;
	while(++i < rect->h)
	{
		ptr = (((rect->y + i) * conf->sl) + rect->x) * conf->bpp;
		j = -1;
		while (j < rect->w)
		{
			ptr += conf->bpp;
			ft_memcpy(ptr, rect->c_bg, conf->bpp);
		}
	}
}

static void	mlx_control_put_init(t_conf *conf, int *y,
	t_rect *rect, t_rect *button)
{
	mlx_string_put(conf->mlx, conf->win,
		FDF_CONTROL_X + FDF_CONTROL_MARGE, *y,
		FDF_CONTROL_TXT2_COLOR, conf->control[i]->title);
	*y += FDF_CONTROL_H + FDF_CONTROL_MARGE;
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

static t_rect	*mlx_control_put_param(t_conf *conf, int *y,
	t_rect *rect, t_rect *button)
{
	rect->y = *y;
	fill_rect(conf->ptr, rect);
	y += FDF_CONTROL_MARGE;
	mlx_string_put(conf->mlx, conf->win, rect->x + FDF_CONTROL_MARGE,
		*y + FDF_CONTROL_MARGE, FDF_CONTROL_TXT1_COLOR, conf->control[i]->p_name[j]);
	mlx_string_put(conf->mlx, conf->win, FDF_CONTROL_V_X + FDF_CONTROL_MARGE,
		*y  + FDF_CONTROL_MARGE, FDF_CONTROL_TXT2_COLOR, conf->control[i]->p_value[j]);
	button->x = FDF_CONTROL_C1_X;
	button->y = *y;
	fill_rect(conf->ptr, button);
	mlx_string_put(conf->mlx, conf->win, button->x  + FDF_CONTROL_MARGE,
		*y +  + FDF_CONTROL_MARGE, FDF_CONTROL_TXT1_COLOR, "-");
	button->x = FDF_CONTROL_C1_X;
	fill_rect(conf->ptr, button);
	mlx_string_put(conf->mlx, conf->win, button->x  + FDF_CONTROL_MARGE,
		*y +  + FDF_CONTROL_MARGE, FDF_CONTROL_TXT1_COLOR, "+");
	*y += FDF_CONTROL_H + FDF_CONTROL_MARGE;
}

static void	mlx_control_put(t_conf *conf)
{
	t_rect	*rect;
	t_rect	*button;
	int		i;
	int		j;
	int		y;

	if(!(rect = (t_rect *)malloc(sizeof(t_rect))))
		set_error("Malloc Echec in mlx_control_put (rect)", 1);
	if(!(button = (t_rect *)malloc(sizeof(t_button))))
		set_error("Malloc Echec in mlx_control_put (button)", 1);
	y = FDF_MARGE + FDF_CONTROL_MARGE;
	i = -1;
	while (++i < 3)
	{
		mlx_control_put_init(conf, &y, rect, button);
		j = 0;
		while (++j < conf->control[i]->p_nb)
		{
			mlx_control_put_param(conf, &y, rect, button);
			set_control_buttons(conf, i, j, y);
		}
	}
	ft_memdel(rect);
	ft_memdel(button);
}

static void	mlx_control_get_world(t_conf *conf)
{
	t_control_c	*cc;

	cc = mlx_control_init_pointers("WORLD", FDF_PARAM_NB_WORLD);
	mlx_control_set_param(cc, 0, "Center X (%)", conf->world->x);
	mlx_control_set_param(cc, 1, "Center Y (%)", conf->world->y);
	mlx_control_set_param(cc, 2, "Center Z (%)", conf->world->z);
	mlx_control_set_param(cc, 3, "Zoom (%)", conf->world->zoom);
	mlx_control_set_param(cc, 4, "Rotate (°)", conf->world->rot);
	conf->control[0] = cc;
}

static void	mlx_control_get_camera(t_conf *conf)
{
	t_control_c	*cc;

	cc = mlx_control_init_pointers("CAMERA", FDF_PARAM_NB_CAMERA);
	mlx_control_set_param(cc, 0, "Position X", conf->camera->x);
	mlx_control_set_param(cc, 1, "Position Y", conf->camera->y);
	mlx_control_set_param(cc, 2, "Position Z", conf->camera->z);
	mlx_control_set_param(cc, 3, "Rotate on X axis (°)", conf->camera->rx);
	mlx_control_set_param(cc, 4, "Rotate on Y axis (°)", conf->camera->ry);
	mlx_control_set_param(cc, 5, "Rotate on Z axis (°)", conf->camera->rz);
	conf->control[1] = cc;
}

static void	mlx_control_get_proj(t_conf *conf)
{
	t_control_c	*cc;

	cc = mlx_control_init_pointers("Projection", FDF_PARAM_NB_PROJ);
	mlx_control_set_param(cc, 0, "1 = parall, 2 = iso, 3 = ???",
		conf->proj->val);
	mlx_control_set_param(cc, 1, "Color gradient ? (0:1)", conf->proj->col);
	mlx_control_set_param(cc, 2, "Color floor", conf->color->floor);
	mlx_control_set_param(cc, 3, "Color ceil", 	conf->color->ceil);
	conf->control[2] = cc;
}

void	mlx_control(t_conf *conf)
{
	mlx_control_get_world(conf);
	mlx_control_get_camera(conf);
	mlx_control_get_proj(conf);
	mlx_control_put(conf, conf->control->control);
}
