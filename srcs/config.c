/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 10:29:08 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/03 15:33:45 by mbaron           ###   ########.fr       */
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
	char	**rgb;
	int		i;

	if (!(colors = ft_strsplit(str_color, '-')))
		set_error("Malloc error in config_color", 1);
	if (2 != ft_strsplitnb(colors))
		set_error("Incorrect param color", 1);
	i = 1;
	while (i--)
	{
		if (!(rgb = ft_strsplit(colors[i], '/')))
			set_error("Malloc error in config_color", 1);
		if (3 != ft_strsplitnb(rgb))
			set_error("Incorrect param color", 1);
		if (i)
		{
			conf->color->ceil->r = ft_atoi(rgb[0]);
			conf->color->ceil->g = ft_atoi(rgb[1]);
			conf->color->ceil->b = ft_atoi(rgb[2]);
		}
		else
		{
			conf->color->floor->r = ft_atoi(rgb[0]);
			conf->color->floor->g = ft_atoi(rgb[1]);
			conf->color->floor->b = ft_atoi(rgb[2]);
		}
		ft_strsplitdel(rgb);
	}
	ft_strsplitdel(colors);
}

t_conf			*config_init(int argc, char *argv[])
{
	t_conf	*conf;
	int		i;

	if (!test_args(argc, argv))
		return (0);
	conf = NULL;
	conf = config_default(conf);
	config_file(conf, CONFIG_FILE_DEFAULT);
	config_map(conf, MAP_FILE_DEFAULT);
	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-f"))
			config_file(conf, argv[i + 1]);
		else if (!ft_strcmp(argv[i], "-m"))
			config_map(conf, argv[i + 1]);
		else if (!ft_strcmp(argv[i], "-c"))
			config_color(conf, argv[i + 1]);
		i += 2;
	}
	return (conf);
}
