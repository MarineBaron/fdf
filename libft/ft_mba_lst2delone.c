/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mba_lst2delone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:50:32 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/05 15:30:34 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_mba_lst2delone(t_list2 **alst, void (*del)(void *, size_t))
{
	if (!alst || !*alst)
		return ;
	if ((*alst)->next)
		(*alst)->next->prev = (*alst)->prev;
	if ((*alst)->prev)
		(*alst)->prev->next = (*alst)->next;
	if (del)
		(*del)((**alst).content, (**alst).content_size);
	free(*alst);
	*alst = NULL;
}
