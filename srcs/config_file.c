/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:37:12 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/15 15:11:51 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

static void		config_file_line(t_conf *conf, char *line)
{
	char	**params;

	if (!(params = ft_strsplit(line, ' ')))
		set_error("Malloc error in config_file_line", 1);
	if (2 == ft_strsplitnb(params) && params[0][0] && params[0][0] != '#')
	{
		if (params[0][0] == 'x')
			conf->control->x = ft_atoi(params[1]);
		else if (params[0][0] == 'y')
			conf->control->y = ft_atoi(params[1]);
		else if (params[0][0] == 'z')
			conf->control->z = ft_atoi(params[1]);
		else if (params[0][0] == 'r')
			conf->control->rot = ft_atoi(params[1]);
		else if (params[0][0] == 'o')
			conf->control->zoom = ft_atoi(params[1]);
		else if (params[0][0] == 'p')
			conf->control->proj = ft_atoi(params[1]);
		else if (params[0][0] == 'g')
			conf->control->col = ft_atoi(params[1]);
		else if (params[0][0] == 'f')
			conf->control->floor = ft_atoi_hex(params[1]);
		else if (params[0][0] == 'c')
			conf->control->ceil = ft_atoi_hex(params[1]);
	}
	ft_strsplitdel(params);
}

void		config_file(t_conf *conf, int argc, char *argv[])
{
	int		fd;
	char	*line;
	int		gnl;
	char	stre[256];
	int		is_config;

	is_config = is_param("-f", argc, argv);
	stre[0] = '\0';
	ft_strclr(stre);
	if (0 > (fd = open(is_config ? argv[is_config] :
		CONFIG_FILE_DEFAULT, O_RDONLY)))
		set_error(ft_strcat(ft_strncpy(stre, is_config
			? argv[is_config]
			: CONFIG_FILE_DEFAULT, 252), " : "), 1);
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
