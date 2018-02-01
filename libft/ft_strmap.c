/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 07:54:14 by mbaron            #+#    #+#             */
/*   Updated: 2017/12/20 15:51:16 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new_s;
	size_t	len;
	size_t	i;

	if (!s || !f)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	if (!(new_s = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_s[i] = f(s[i]);
		i++;
	}
	new_s[len] = '\0';
	return (new_s);
}
