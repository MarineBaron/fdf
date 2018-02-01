/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mba_lst2find.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:51:39 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/05 17:57:08 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list2	*ft_mba_lst2find(t_list2 **alst, t_list2 *to_find)
{
	t_list2	*tmp;

	if (!to_find || !alst || !*alst)
		return (NULL);
	tmp = *alst;
	while (tmp && tmp != to_find)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp);
}
