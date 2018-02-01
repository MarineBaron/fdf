/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mba_lstfind.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 08:24:36 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/05 12:13:11 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_mba_lstfind(t_list **alst, t_list *to_find)
{
	t_list	*tmp;

	if (!to_find || !alst || !*alst)
		return (NULL);
	tmp = *alst;
	while (tmp && tmp != to_find)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp);
}
