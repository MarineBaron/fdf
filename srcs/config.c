/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 10:29:08 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/04 23:04:43 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

static void		config_file(t_conf *conf, char *file)
{
	int		fd;
	char	*line;
	int		gnl;
	char	stre[256];
	int		i;

	stre[0] = '\0';
	ft_strclr(stre);
	if (0 > (fd = open(file, O_RDONLY)))
		set_error(ft_strcat(ft_strncpy(stre, file, 252), " : "), 1);
	if (!(line = ft_strnew(0)))
		set_error("Malloc error in config_fdf", 1);
	while ((gnl = get_next_line(fd, &line)))
	{
		if (-1 == gnl)
			set_error("Error in GNL", 1);
		i = 0;
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] && line[i] != '#')
			config_file_line(conf, line);;
	}
	ft_strdel(&line);
}

static void		config_map(t_conf *conf, char *file)
{
	if (!(conf->mapi = (t_mapi *)malloc(sizeof(t_mapi))))
		set_error("Malloc error in config_map", 1);
	conf->mapi->h = 0;
	conf->mapi->w = 0;
	map_parse_file(conf, file);
}

static void		config_color(t_conf *conf, char *str_color)
{
	char	**colors;

	if (!(colors = ft_strsplit(str_color, '-')))
		set_error("Malloc error in config_color", 1);
	if (2 != ft_strsplitnb(colors))
		set_error("Incorrect param color", 1);
	conf->color->floor = ft_atoi_hex(colors[0]);
	conf->color->ceil = ft_atoi_hex(colors[1]);
	ft_strsplitdel(colors);
}

t_conf			*config_init(int argc, char *argv[])
{
	t_conf	*conf;
	int		i;
	int		is_map;

	if (!test_args(argc, argv))
		return (0);
	conf = NULL;
	conf = config_default(conf);
	config_file(conf, CONFIG_FILE_DEFAULT);
	i = 1;
	is_map = 0;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-f"))
			config_file(conf, argv[i + 1]);
		else if (!ft_strcmp(argv[i], "-m"))
		{
			config_map(conf, argv[i + 1]);
			is_map = 1;
		}
		else if (!ft_strcmp(argv[i], "-c"))
			config_color(conf, argv[i + 1]);
		i += 2;
	}
	if (!is_map)
		config_map(conf, MAP_FILE_DEFAULT);
	return (conf);
}
