/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 18:19:50 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/05 11:52:04 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		remove_current(t_lstfd **begin, t_lstfd *current)
{
	t_lstfd	*tmp;
	t_lstfd	*prev;

	prev = NULL;
	tmp = *begin;
	while (tmp && tmp != current)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == *begin)
		*begin = current->next;
	else
		prev->next = current->next;
	free(current->str);
	current->str = NULL;
	free(current);
	current = NULL;
}

static int		get_new_str(char **line, t_lstfd **begin, t_lstfd *current)
{
	int		endl;
	char	*tmp;

	if (current->str)
	{
		endl = 0;
		while (current->str[endl] && current->str[endl] != '\n')
			endl++;
		if (!(tmp = ft_strsub(current->str, 0, endl)))
			return (-1);
		ft_strdel(line);
		*line = tmp;
		if (ft_strchr(current->str, '\n') || endl)
		{
			if (ft_strchr(current->str, '\n'))
				ft_strcpy(current->str, current->str + endl + 1);
			else if (endl)
				ft_strcpy(current->str, current->str + endl);
			return (1);
		}
	}
	remove_current(begin, current);
	return (0);
}

static	t_lstfd	*get_lstfd(t_lstfd **begin, int fd)
{
	t_lstfd	*tmp;

	tmp = *begin;
	while (tmp && tmp->fd != fd)
		tmp = tmp->next;
	if (!tmp)
	{
		if (!(tmp = (t_lstfd *)malloc(sizeof(t_lstfd))))
			return (NULL);
		tmp->fd = fd;
		tmp->str = NULL;
		if (!(tmp->tmp = ft_strnew(0)))
			return (NULL);
		tmp->next = *begin;
		*begin = tmp;
	}
	return (tmp);
}

int				get_next_line(int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_lstfd	*begin;
	t_lstfd			*current;
	int				res;

	if (fd < 0 || BUFF_SIZE <= 0 || !line || read(fd, buf, 0) < 0)
		return (-1);
	if (!begin)
		begin = NULL;
	if (!(current = get_lstfd(&begin, fd)))
		return (-1);
	while ((!ft_strchr(current->tmp, '\n')))
	{
		res = read(fd, buf, BUFF_SIZE);
		if (res < 1)
			return (!res ? get_new_str(line, &begin, current) : -1);
		buf[res] = '\0';
		if (!(current->str = ft_strjoin(current->tmp, buf)))
			return (-1);
		if (current->tmp)
			free(current->tmp);
		current->tmp = current->str;
	}
	return (get_new_str(line, &begin, current));
}
