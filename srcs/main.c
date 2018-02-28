/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 09:24:52 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/28 19:04:50 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char *argv[])
{
	t_conf	*conf;

	if (!(conf = config_init(argc, argv)))
	{
		destroy(conf);
		return (1);
	}
	ft_putendl("Config is OK, you can play !!!");
	render(conf);
	mlx_hook(conf->win, 2, 0, hook_keydown, conf);
	mlx_hook(conf->win, 3, 0, hook_keyup, conf);
	mlx_hook(conf->win, 4, 0, hook_mousedown, conf);
	mlx_hook(conf->win, 5, 0, hook_mouseup, conf);
	mlx_hook(conf->win, 6, 0, hook_mousemove, conf);
	mlx_hook(conf->win, 17, 0, hook_close, conf);
	mlx_loop(conf->mlx);
	ft_putendl("Bye, bye !!!");
	return (0);
}
