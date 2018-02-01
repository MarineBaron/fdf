/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mba_lstnew.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:42:28 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/05 18:44:02 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_mba_lstnew(void const *content, size_t content_size)
{
	t_list	*tmp;

	if (!(tmp = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	tmp->next = NULL;
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
