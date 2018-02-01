/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mba_lst2remone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 18:23:53 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/05 18:42:13 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_mba_lst2remone(t_list2 **alst, t_list2 *to_rem,
		void (*del)(void *, size_t))
{
	t_list2			*tmp;
	t_list2			*tmp_prev;

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
	if (tmp->next)
		tmp->next->prev = tmp_prev;
	ft_mba_lst2delone(&tmp, del);
}
