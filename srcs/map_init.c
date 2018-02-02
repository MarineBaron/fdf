/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:03:30 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/02 12:01:22 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

static void	map_add_vertex(t_lstmapi **p_lstmapi, double x, double y, double z)
{
	t_lstmapi	*tmp;
	t_vertex	*vertex;

	if (!(vertex = (t_vertex *)malloc(sizeof(t_vertex))))
		set_error("Malloc error in map_add_vertex", 1);
	vertex->x = x;
	vertex->y = y;
	vertex->z = z;
	if (!(tmp = (t_lstmapi *)malloc(sizeof(t_lstmapi))))
		set_error("Malloc error in map_add_vertex", 1);
	tmp->vertex = vertex;
	tmp->next = *p_lstmapi;
	*p_lstmapi = tmp;
}

static void	map_init_line(t_conf *conf, char *str, t_lstmapi *lstmapi)
{
	char		**nbrs;
	int			c;
	int			l;

	l = conf->mapi->h;
	c = 0;
	nbrs = ft_strsplit(str, ' ');
	while (*nbrs)
	{
		map_add_vertex(&lstmapi, (double)c, (double)l, ft_getnbr(*nbrs));
		c++;
		if (c > conf->mapi->w)
			conf->mapi->w = c;
		free(*nbrs);
		*nbrs = NULL;
		nbrs++;
	}
	free(*nbrs);
	free(nbrs);
	nbrs = NULL;
	conf->mapi->h += 1;
}

void		map_parse_file(t_conf *conf, char *file, t_lstmapi *lstmapi)
{
	int			fd;
	char		*line;
	int			gnl;
	char		stre[256];

	ft_strclr(stre);
	if (0 > (fd = open(file, O_RDONLY)))
		set_error(ft_strcat(ft_strncpy(stre, file, 252), " : "), 1);
	if (!(line = ft_strnew(0)))
		set_error("Malloc error in config_map", 1);
	while ((gnl = get_next_line(fd, &line)))
	{
		if (-1 == gnl)
			set_error("Error in GNL", 1);
		map_init_line(conf, line, lstmapi);
	}
	if (line)
		free(line);
}
