/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 15:38:00 by mbaron            #+#    #+#             */
/*   Updated: 2017/12/20 15:47:34 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	unsigned char	*zone;
	size_t			i;

	if (!(zone = (unsigned char *)malloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
		zone[i++] = '\0';
	return ((void *)zone);
}
