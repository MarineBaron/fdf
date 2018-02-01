/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mba_lstlen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 17:07:16 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/05 09:10:25 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

unsigned int	ft_mba_lstlen(t_list **alst)
{
	unsigned int	l;
	t_list			*tmp;

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
