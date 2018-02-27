/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 10:29:08 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/26 08:41:35 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

int				is_param(const char *param, int argc, char *argv[])
{
	int		i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(param, argv[i]))
			return (i + 1);
	}
	return (0);
}

t_conf			*config_default(void)
{
	t_conf	*conf;

	conf = (t_conf *)init_pointer(sizeof(t_conf),
		"Error malloc in config_default (conf)");
	conf->control = (t_control *)init_pointer(sizeof(t_control),
		"Error malloc in config_default (control)");
	conf->control->v = (t_values *)init_pointer(sizeof(t_values),
		"Error malloc in config_default (v)");
	conf->control->nb = FDF_P_NB;
	conf->control->v->x = FDF_P_X;
	conf->control->v->y = FDF_P_Y;
	conf->control->v->z = FDF_P_Z;
	conf->control->v->zoom = FDF_P_O;
	conf->control->v->rot = FDF_P_R;
	conf->control->v->proj = FDF_P_P;
	conf->control->v->col = FDF_P_G;
	conf->control->v->floor = FDF_P_F;
	conf->control->v->ceil = FDF_P_C;
	conf->control->p = (t_param **)init_pointer(
		conf->control->nb * sizeof(t_param *),
		"Error malloc in config_default (params)");
	config_set_params(conf, conf->control->p);
	return (conf);
}

static void		config_color(t_conf *conf, int argc, char *argv[])
{
	char	**colors;
	int		is_color;

	is_color = is_param("-c", argc, argv);
	if (!is_color)
		return ;
	if (!(colors = ft_strsplit(argv[is_color], '-')))
		set_error("Malloc error in config_color", 1);
	if (2 != ft_strsplitnb(colors))
		set_error("Incorrect param color", 1);
	conf->control->v->floor = ft_atoi_hex(colors[0]);
	conf->control->v->ceil = ft_atoi_hex(colors[1]);
	ft_strsplitdel(colors);
}

static void		config_map(t_conf *conf, int argc, char *argv[])
{
	int		is_map;

	is_map = is_param("-m", argc, argv);
	conf->mapi = (t_mapi *)init_pointer(sizeof(t_mapi),
		"Malloc error in config_map");
	conf->mapi->h = 0;
	conf->mapi->w = 0;
	map_parse_file(conf, is_map ? argv[is_map] : MAP_FILE_DEFAULT);
}

t_conf			*config_init(int argc, char *argv[])
{
	t_conf	*conf;

	if (!test_args(argc, argv))
		return (NULL);
	conf = config_default();
	config_file(conf, argc, argv);
	config_color(conf, argc, argv);
	config_map(conf, argc, argv);
	return (conf);
}
