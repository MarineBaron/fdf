/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:59:27 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/26 13:32:20 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (!needle[0])
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = i;
		k = 0;
		while (haystack[j] == needle[k])
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
