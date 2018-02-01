/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 16:23:21 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/26 13:31:10 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (!needle[0])
		return ((char *)haystack);
	i = 0;
	j = 0;
	k = 0;
	while (haystack[i] && i < len)
	{
		j = i;
		k = 0;
		while (j < len && haystack[j] == needle[k])
		{
			j++;
			k++;
			if (!needle[k])
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
