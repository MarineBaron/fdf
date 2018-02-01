/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:35:01 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/01 13:42:58 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# define BUFF_SIZE 8

typedef struct	s_lstfd
{
	int				fd;
	char			*str;
	char			*tmp;
	struct s_lstfd	*next;
}				t_lstfd;
int				get_next_line(int fd, char **line);
#endif
