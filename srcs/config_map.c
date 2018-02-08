/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:03:30 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/08 07:49:10 by mbaron           ###   ########.fr       */
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
		ft_strdel(&hex);
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

static void		map_init_line(t_conf *conf, char *line, t_lstmapi **lstmapi)
{
	char		**nbrs;
	int			c;
	int			i;

	c = 0;
	if (!(nbrs = ft_strsplit(line, ' ')))
		set_error("Malloc error in map_init_line", 1);
	i = -1;
	while (nbrs[++i])
	{
		map_add_vertex(lstmapi, (double)c, (double)conf->mapi->h, nbrs[i]);
		c++;
		if (c > conf->mapi->w)
			conf->mapi->w = c;
	}
	ft_strsplitdel(nbrs);
	conf->mapi->h += 1;
}

static void		map_create(t_conf *conf, t_lstmapi *lstmapi)
{
	t_lstmapi	*tmp;
	t_vertex	***vertexes;
	int			i;

	vertexes = (t_vertex ***)init_pointer(conf->mapi->h * sizeof(t_vertex **),
		"Malloc error in map_create (vertexes)");
	i = -1;
	while (++i < conf->mapi->h)
		vertexes[i] = (t_vertex **)init_pointer(conf->mapi->w
			* sizeof(t_vertex *), "Malloc error in map_create (vertexes[i])");
	tmp = lstmapi;
	while (lstmapi)
	{
		vertexes[conf->mapi->h - (int)tmp->vertex->y - 1]
			[(int)tmp->vertex->x] = tmp->vertex;
		tmp = lstmapi->next;
		ft_memdel((void **)&lstmapi);
		lstmapi = tmp;
	}
	conf->mapi->vertexes = vertexes;
	conf->map = (t_map *)init_pointer(sizeof(t_map),
		"Malloc error in map_create (conf->map)");
	conf->map->rect = (t_rect *)init_pointer(sizeof(t_rect),
		"Malloc error in map_create (conf->map->rect)");
	conf->map->rect->x = FDF_MAP_X;
	conf->map->rect->y = FDF_MAP_Y;
	conf->map->rect->w = FDF_MAP_W;
	conf->map->rect->h = FDF_MAP_H;
	conf->map->rect->c_bg = FDF_MAP_BG_COLOR;
	conf->map->rect->c_bd = FDF_MAP_BD_COLOR;
	conf->map->vectors = NULL;
}

void			map_parse_file(t_conf *conf, char *file)
{
	int			fd;
	char		*line;
	int			gnl;
	char		stre[256];
	t_lstmapi	*lstmapi;

	stre[0] = '\0';
	ft_strclr(stre);
	if (0 > (fd = open(file, O_RDONLY)))
		set_error(ft_strcat(ft_strncpy(stre, file, 252), " : "), 1);
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
