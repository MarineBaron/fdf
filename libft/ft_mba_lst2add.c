/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mba_lst2add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 17:00:07 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/05 18:41:34 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_mba_lst2add(t_list2 **alst, t_list2 *new)
{
	if (!alst || !new)
		return ;
	(*alst)->prev = new;
	new->next = *alst;
	*alst = new;
}
