/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:54:33 by mbaron            #+#    #+#             */
/*   Updated: 2017/12/01 21:15:31 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	if (!c)
		return ((char *)s);
	while (i && *s != (char)c)
	{
		s--;
		i--;
	}
	return (*s == (char)c ? (char *)s : NULL);
}
