/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:03:30 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/15 12:43:50 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

static t_col	map_get_color(char *str)
{
	t_col		col;
	char		*hex;

	if ((hex = ft_strchr(str, ',')))
	{
		col = ft_atoi_hex(hex + 1);
	}
	else
		col = 0;
	return (col);
}

static void		map_add_vertex(t_lstmapi **p_lstmapi, double x, double y,
	char *str)
{
	t_lstmapi	*tmp;
	t_vertex	*vertex;

	if (!(vertex = (t_vertex *)malloc(sizeof(t_vertex))))
		set_error("Malloc error in map_add_vertex (vertex)", 1);
	vertex->x = x;
	vertex->y = y;
	vertex->z = (double)ft_atoi(str);
	vertex->c = map_get_color(str);
	if (!(tmp = (t_lstmapi *)malloc(sizeof(t_lstmapi))))
		set_error("Malloc error in map_add_vertex (tmp)", 1);
	tmp->vertex = vertex;
	tmp->next = *p_lstmapi;
	*p_lstmapi = tmp;
}

static void		map_init_line(t_conf *conf, char *line,
	t_lstmapi **lstmapi)
{
	char		**nbrs;
	int			i;
	int			j;

	if (!(nbrs = ft_strsplit(line, ' ')))
		set_error("Malloc error in map_init_line", 1);
	i = 0;
	j = -1;
	while (nbrs[++j])
	{
		map_add_vertex(lstmapi, (double)j, (double)conf->mapi->h, nbrs[j]);
		i++;
	}
	if (!conf->mapi->h)
		conf->mapi->w = i;
	else if (i != conf->mapi->w)
		set_error("Map is invalid", 1);
	conf->mapi->h += 1;
	ft_strsplitdel(nbrs);
}

void			map_parse_file(t_conf *conf, char *file)
{
	int			fd;
	char		*line;
	int			gnl;
	t_lstmapi	*lstmapi;

	if (0 > (fd = open(file, O_RDONLY)))
		set_error("Open error on map file", 1);
	if (!(line = ft_strnew(0)))
		set_error("Malloc error in map_parse_file", 1);
	lstmapi = NULL;
	while ((gnl = get_next_line(fd, &line)))
	{
		if (-1 == gnl)
			set_error("Error in GNL", 1);
		map_init_line(conf, line, &lstmapi);
	}
	ft_strdel(&line);
	map_create(conf, lstmapi);
}
