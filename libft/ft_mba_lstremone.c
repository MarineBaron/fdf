/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mba_lstremone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 18:23:25 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/05 18:44:46 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_mba_lstremone(t_list **alst, t_list *to_rem,
		void (*del)(void *, size_t))
{
	t_list			*tmp;
	t_list			*tmp_prev;

	if (!to_rem || !alst || !*alst)
		return ;
	tmp = *alst;
	tmp_prev = NULL;
	while (tmp && tmp != to_rem)
	{
		tmp_prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	if (tmp_prev)
		tmp_prev->next = tmp->next;
	ft_lstdelone(&tmp, del);
}
