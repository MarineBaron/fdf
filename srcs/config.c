/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 10:29:08 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/01 19:37:13 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

static int		config_file(t_conf *conf, char *file)
{
	int		fd;
	char	*line;
	int		gnl;
	char	stre[256];
	int		i;

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
			config_file_line(conf, line, &i);
	}
	if (line)
		free(line);
	return (1);
}

static int		config_map(t_conf *conf, char *file)
{
	int		fd;
	char	*line;
	int		gnl;
	char	stre[256];
	t_lstp	*list;
	
	ft_strclr(stre);
	if (0 > (fd = open(file, O_RDONLY)))
		set_error(ft_strcat(ft_strncpy(stre, file, 252), " : "), 1);
	if (!(line = ft_strnew(0)))
		set_error("Malloc error in config_map", 1);
	while ((gnl = get_next_line(fd, &line)))
	{
		if (-1 == gnl)
			set_error("Error in GNL", 1);
		map_init_line(conf, line, list);
	}
	if (line)
		free(line);	
	return (1);
}

static int		config_color(t_conf *conf, char *filename)
{
	return (1);
}

int				config_init(int argc, char *argv[], t_conf *conf)
{
	int		i;

	if (!test_args(argc, argv))
		return (0);
	conf = config_default(conf);
	config_file(conf, CONFIG_FILE_DEFAULT);
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
	return (1);
}
