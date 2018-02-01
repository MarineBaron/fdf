/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mba_lst2new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:44:36 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/05 15:04:51 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list2	*ft_mba_lst2new(void const *content, size_t content_size)
{
	t_list2	*tmp;

	if (!(tmp = (t_list2 *)malloc(sizeof(t_list))))
		return (NULL);
	tmp->next = NULL;
	tmp->prev = NULL;
	if (!content || !content_size)
	{
		tmp->content_size = 0;
		tmp->content = NULL;
		return (tmp);
	}
	tmp->content = (void *)malloc(sizeof(void *));
	tmp->content = (void *)content;
	tmp->content_size = content_size;
	return (tmp);
}
