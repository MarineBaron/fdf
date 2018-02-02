/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 09:24:52 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/02 18:19:07 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_conf(t_conf *conf)
{
	ft_putendl("CONF:");
	printf("conf (p): %p\n", conf);
	printf("conf.world (p): %p\n", conf->world);
}

int		main(int argc, char *argv[])
{
	t_conf	*conf;

	conf = NULL;
	if (!(conf = config_init(argc, argv)))
		return (1);
	put_conf(conf);
	ft_putendl("Tests are OK, you can begin !!!");
	return (0);
}
