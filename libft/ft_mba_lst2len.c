/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mba_lst2len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 17:12:02 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/05 14:41:33 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

unsigned int	ft_mba_lst2len(t_list2 **alst)
{
	unsigned int	l;
	t_list2			*tmp;

	if (!alst || !*alst)
		return (0);
	tmp = *alst;
	l = 0;
	while (tmp)
	{
		l++;
		tmp = tmp->next;
	}
	return (l);
}
