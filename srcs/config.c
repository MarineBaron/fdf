/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 10:29:08 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/08 07:10:52 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

static int	is_param(const char *param, int argc, char *argv[])
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

static void	config_file(t_conf *conf, int argc, char *argv[])
{
	int		fd;
	char	*line;
	int		gnl;
	char	stre[256];
	int		is_config;

	is_config = is_param("-f", argc, argv);
	stre[0] = '\0';
	ft_strclr(stre);
	if (0 > (fd = open(is_config ? argv[is_config] : CONFIG_FILE_DEFAULT,
		O_RDONLY)))
		set_error(ft_strcat(ft_strncpy(stre,
			is_config ? argv[is_config] : CONFIG_FILE_DEFAULT, 252), " : "), 1);
	if (!(line = ft_strnew(0)))
		set_error("Malloc error in config_file", 1);
	while ((gnl = get_next_line(fd, &line)))
	{
		if (-1 == gnl)
			set_error("Error in GNL", 1);
		config_file_line(conf, line);
	}
	ft_strdel(&line);
}

static void	config_color(t_conf *conf, int argc, char *argv[])
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
	conf->color->floor = ft_atoi_hex(colors[0]);
	conf->color->ceil = ft_atoi_hex(colors[1]);
	ft_strsplitdel(colors);
}

static void	config_map(t_conf *conf, int argc, char *argv[])
{
	int		is_map;

	is_map = is_param("-m", argc, argv);
	conf->mapi = (t_mapi *)init_pointer(sizeof(t_mapi),
		"Malloc error in config_map");
	conf->mapi->h = 0;
	conf->mapi->w = 0;
	map_parse_file(conf, is_map ? argv[is_map] : MAP_FILE_DEFAULT);
}

t_conf		*config_init(int argc, char *argv[])
{
	t_conf	*conf;

	if (!test_args(argc, argv))
		return (NULL);
	conf = config_default();
	config_file(conf, argc, argv);
	config_color(conf, argc, argv);
	config_control_set_world(conf);
	config_control_set_camera(conf);
	config_control_set_proj(conf);
	config_control_set_pos(conf);
	config_map(conf, argc, argv);
	return (conf);
}
