/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mba_lstaddafter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 17:30:05 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/05 17:12:42 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_mba_lstaddafter(t_list **head, t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (!head || !*head || !alst || !*alst || !new)
		return ;
	tmp = *head;
	while (tmp && tmp != *alst)
		tmp = tmp->next;
	if (*alst && !tmp)
		return ;
	new->next = tmp->next;
	tmp->next = new;
	*alst = new;
}
