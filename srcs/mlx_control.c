/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:13:51 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/05 17:42:24 by mbaron           ###   ########.fr       */
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
	if (!(cc->i_value = (t_mba_img *)malloc(nb * sizeof(t_mba_img))))
		set_error("Malloc Echec in mlx_control_get_world (values)", 1);
	if (!(cc->i_control = (t_mba_img *)malloc(2 * nb * sizeof(t_mba_img))))
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

static void	mlx_control_set_images(t_conf *conf, t_control_c *cc)
{
	t_mba_img	*img;
	int			i;
	static int	y;
	
	if (!y)
		y = FDF_MARGE + FDF_CONTROL_MARGE;
	
	mlx_string_put(conf->mlx, conf->win, FDF_CONTROL_X + FDF_CONTROL_MARGE, y,
		FDF_CONTROL_TXT2_COLOR, cc->title);
	y += FDF_CONTROL_H + FDF_CONTROL_MARGE;
	img = NULL;
	if(!(img = (t_mba_img *)malloc(sizeof(t_mba_img))))
		set_error("yMalloc Echec in mlx_control_set_params (img)", 1);
	img->x = FDF_CONTROL_X;
	img->w = FDF_CONTROL_W;
	img->h = FDF_CONTROL_H;
	img->c_bg = FDF_CONTROL_BG_COLOR;
	img->c_bd = FDF_CONTROL_BD_COLOR;
	img->mlx = NULL;
	if(!(img->mlx = mlx_new_image(conf->mlx, img->w, img->h)))
		set_error("Malloc Echec in mlx_control_set_params (mlx_img)", 1);
	img->ptr = mlx_get_data_addr(img->mlx, &img->bpp, &img->sl, &img->ent);
	printf("mlx_control_set_images0 img:%p mlx:%p ptr:%p\n", img, img->mlx, img->ptr);
	ft_memset((void *)img->ptr, 15, img->w * img->h * img->bpp);
	printf("mlx_control_set_images1 img:%p mlx:%p ptr:%p\n", img, img->mlx, img->ptr);
	i = -1;
	while (++i < cc->p_nb)
	{
		printf("mlx_control_set_images3 img:%p mlx:%p ptr:%p\n", img, img->mlx, img->ptr);
		img->y = y;
		mlx_put_image_to_window(conf->mlx, conf->win, img->mlx, img->x, img->y);
		y += FDF_CONTROL_MARGE;
		mlx_string_put(conf->mlx, conf->win, FDF_CONTROL_P_X, y,
			FDF_CONTROL_TXT1_COLOR, cc->p_name[i]);
		mlx_string_put(conf->mlx, conf->win, FDF_CONTROL_V_X, y,
			FDF_CONTROL_TXT2_COLOR, cc->p_value[i]);
		y += FDF_CONTROL_H + FDF_CONTROL_MARGE;
	}
	printf("mlx_control_set_images4 img:%p mlx:%p ptr:%p\n", img, img->mlx, img->ptr);
	if (img)
	{
		if (img->mlx)
		{
			mlx_destroy_image(conf->mlx, img->mlx);
			img->mlx = NULL;
			img->ptr = NULL;
		}
		ft_memdel((void **)&img);
	}
	img = NULL;
	printf("mlx_control_set_images5 img:%p\n", img);
}

static void	mlx_control_get_world(t_conf *conf, t_control *control)
{
	t_control_c	*cc;

	cc = mlx_control_init_pointers("WORLD", FDF_PARAM_NB_WORLD);
	mlx_control_set_param(cc, 0, "Center X (%)", conf->world->x);
	mlx_control_set_param(cc, 1, "Center Y (%)", conf->world->y);
	mlx_control_set_param(cc, 2, "Center Z (%)", conf->world->z);
	mlx_control_set_param(cc, 3, "Zoom (%)", conf->world->zoom);
	mlx_control_set_param(cc, 4, "Rotate (°)", conf->world->rot);
	control->control[0] = cc;
}

static void	mlx_control_get_camera(t_conf *conf, t_control *control)
{
	t_control_c	*cc;

	cc = mlx_control_init_pointers("CAMERA", FDF_PARAM_NB_CAMERA);
	mlx_control_set_param(cc, 0, "Position X", conf->camera->x);
	mlx_control_set_param(cc, 1, "Position Y", conf->camera->y);
	mlx_control_set_param(cc, 2, "Position Z", conf->camera->z);
	mlx_control_set_param(cc, 3, "Rotate on X axis (°)", conf->camera->rx);
	mlx_control_set_param(cc, 4, "Rotate on Y axis (°)", conf->camera->ry);
	mlx_control_set_param(cc, 5, "Rotate on Z axis (°)", conf->camera->rz);
	control->control[1] = cc;
}

static void	mlx_control_get_proj(t_conf *conf, t_control *control)
{
	t_control_c	*cc;

	cc = mlx_control_init_pointers("Projection", FDF_PARAM_NB_PROJ);
	mlx_control_set_param(cc, 0, "1 = parall, 2 = iso, 3 = ???",
		conf->proj->val);
	mlx_control_set_param(cc, 1, "Color gradient ? (0:1)", conf->proj->col);
	mlx_control_set_param(cc, 2, "Color floor", conf->color->floor);
	mlx_control_set_param(cc, 3, "Color ceil", 	conf->color->ceil);
	control->control[2] = cc;
}

void	mlx_control_init(t_conf *conf)
{
	t_control	*control;
	int			i;

	control = NULL;
	if (!(control = (t_control *)malloc(sizeof(t_control))))
		set_error("Maloc Echec in mlx_control_init", 1);
	control->x = FDF_CONTROL_X;
	control->y = FDF_CONTROL_Y;
	control->w = FDF_CONTROL_W;
	control->h = FDF_CONTROL_W;
	mlx_control_get_world(conf, control);
	mlx_control_get_camera(conf, control);
	mlx_control_get_proj(conf, control);
	conf->control = control;
	i = -1;
	while (++i < 3)
		mlx_control_set_images(conf, control->control[i]);
}
