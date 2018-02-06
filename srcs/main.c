/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 09:24:52 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/06 18:14:30 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_conf(t_conf *conf)
{
	ft_putendl("CONF:");
	printf("conf world.x:%d \n", conf->world->x);
	printf("conf world.y:%d \n", conf->world->y);
	printf("conf world.zoom:%d \n", conf->world->zoom);
	printf("conf world.rot:%d \n", conf->world->rot);
	printf("conf cam.x:%d \n", conf->camera->x);
	printf("conf cam.y:%d \n", conf->camera->y);
	printf("conf cam.z:%d \n", conf->camera->z);
	printf("conf cam.rx:%d \n", conf->camera->rx);
	printf("conf cam.ry:%d \n", conf->camera->ry);
	printf("conf cam.rz:%d \n", conf->camera->rz);
	printf("conf proj.val:%d \n", conf->proj->val);
	printf("conf color.floor:%d \n", conf->color->floor);
	printf("conf color.ceil:%d \n", conf->color->ceil);
}

static void	clear(t_conf *conf)
{
	int		i;
	int		j;

	free(conf->world);
	free(conf->camera);
	free(conf->proj);
	free(conf->color);
	i = -1;
	while (++i < conf->mapi->h)
	{
		j = -1;
		while (++j < conf->mapi->w)
		{
			free(conf->mapi->mapi[i][j]);
			conf->mapi->mapi[i][j] = NULL;
		}
		free(conf->mapi->mapi[i]);
		conf->mapi->mapi[i] = NULL;
	}
	free(conf->mapi->mapi);
	conf->mapi->mapi = NULL;
	free(conf->mapi);
	conf->mapi = NULL;
	free(conf);
	conf = NULL;
}

static void	render(t_conf *conf)
{
	conf->mlx = NULL;
	if (!(conf->mlx = mlx_init()))
		set_error("Echec in MLX init", 1);
	conf->win = NULL;
	if (!(conf->win = mlx_new_window(conf->mlx, FDF_WIN_W, FDF_WIN_H,
		"My map")))
		set_error("Echec in MLX new window", 1);
	conf->img = NULL;
	if (!(conf->img = mlx_new_image(conf->mlx, FDF_WIN_W, FDF_WIN_H)))
		set_error("Echec in MLX new image", 1);
	conf->ptr = mlx_get_data_addr(conf->img, &conf->bpp, &conf->sl, &conf->end);
	conf->bpp /= 8;
	mlx_control(conf);
	mlx_map(conf);
	mlx_put_image_to_window(conf->mlx, conf->win, conf->img, 0, 0);
	mlx_control_put_txt(conf);
}

int		main(int argc, char *argv[])
{
	t_conf	*conf;

	conf = NULL;
	if (!(conf = config_init(argc, argv)))
		return (1);
	put_conf(conf);
	ft_putendl("Tests are OK, you can begin !!!");
	render(conf);
	mlx_key_hook(conf->win, hook_key, conf);
	mlx_mouse_hook(conf->win, hook_mouse, conf);
	mlx_loop(conf->mlx);
	clear(conf);
	return (0);
}
