/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 15:13:16 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/26 13:36:02 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_putstr_array(char *tab[], size_t tabl)
{
	size_t	i;

	i = 0;
	while (i < tabl)
	{
		ft_putendl(tab[i]);
		i++;
	}
}
