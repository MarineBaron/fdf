/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 09:24:52 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/03 15:38:48 by mbaron           ###   ########.fr       */
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
	printf("conf color.floor.r:%d \n", conf->color->floor->r);
	printf("conf color.floor.g:%d \n", conf->color->floor->g);
	printf("conf color.floor.b:%d \n", conf->color->floor->b);
	printf("conf color.ceil.r:%d \n", conf->color->ceil->r);
	printf("conf color.ceil.g:%d \n", conf->color->ceil->g);
	printf("conf color.ceil.b:%d \n", conf->color->ceil->b);
}

static void conf_clear(t_conf *conf) {
	int		i;
	int		j;

	free(conf->world);
	free(conf->camera);
	free(conf->proj);
	free(conf->color->floor);
	free(conf->color->ceil);
	free(conf->color);
	i = -1;
	while(++i < conf->mapi->h)
	{
		j = -1;
		while(++j < conf->mapi->w)
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

int		main(int argc, char *argv[])
{
	t_conf	*conf;

	conf = NULL;
	if (!(conf = config_init(argc, argv)))
		return (1);
	put_conf(conf);
	ft_putendl("Tests are OK, you can begin !!!");
	conf_clear(conf);
	return (0);
}
