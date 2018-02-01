/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 09:36:08 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/05 08:16:52 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*tmp_next;

	if (!alst || !*alst)
		return ;
	tmp = *alst;
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
