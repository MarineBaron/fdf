/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mba_lst2addafter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:35:38 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/05 17:12:39 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_mba_lst2addafter(t_list2 **head, t_list2 **alst, t_list2 *new)
{
	t_list2	*tmp;

	if (!head || !*head || !alst || !*alst || !new)
		return ;
	tmp = *head;
	while (tmp && tmp != *alst)
		tmp = tmp->next;
	if (*alst && !tmp)
		return ;
	new->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = new;
	tmp->next = new;
	new->prev = tmp;
	*alst = new;
}
