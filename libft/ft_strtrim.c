/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 09:24:41 by mbaron            #+#    #+#             */
/*   Updated: 2017/12/21 09:20:13 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	char	*ret;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	j = len - 1;
	while (j > i && (s[j] == ' ' || s[j] == '\n' || s[j] == '\t'))
		j--;
	len -= i + len - j - 1;
	if (!(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	j = 0;
	while (j < len)
		ret[j++] = s[i++];
	ret[j] = '\0';
	return (ret);
}
