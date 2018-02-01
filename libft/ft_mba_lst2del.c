/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mba_lstdel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:53:27 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/05 17:42:31 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_mba_lst2del(t_list2 **alst, void (*del)(void *, size_t))
{
	t_list2	*tmp;
	t_list2	*tmp_next;

	if (!alst || !*alst)
		return ;
	tmp = *alst;
	if (tmp->prev)
		tmp->prev->next = NULL;
	while (tmp)
	{
		if (del)
			(*del)(tmp->content, tmp->content_size);
		tmp_next = tmp->next;
		free(tmp);
		tmp = tmp_next;
	}
	*alst = NULL;
}
