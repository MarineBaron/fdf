/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:03:30 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/05 10:07:37 by mbaron           ###   ########.fr       */
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
	t_vertex	***mapi;
	int			i;
	int			j;

	if (!(mapi = (t_vertex ***)malloc(conf->mapi->h * sizeof(t_vertex **))))
		set_error("Malloc error in map_create", 1);
	i = -1;
	while (++i < conf->mapi->h)
	{
		if (!(mapi[i] = (t_vertex **)malloc(conf->mapi->w
			* sizeof(t_vertex *))))
			set_error("Malloc error in map_create", 1);
		j = -1;
		while (++j < conf->mapi->w)
			mapi[i][j] = NULL;
	}
	tmp = lstmapi;
	while (lstmapi)
	{
		mapi[conf->mapi->h - (int)tmp->vertex->y - 1]
			[(int)tmp->vertex->x] = tmp->vertex;
		tmp = lstmapi->next;
		free(lstmapi);
		lstmapi = tmp;
	}
	conf->mapi->mapi = mapi;
}

void		map_parse_file(t_conf *conf, char *file)
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
