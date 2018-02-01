/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 09:08:57 by mbaron            #+#    #+#             */
/*   Updated: 2017/12/21 16:39:39 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	len = s1 ? ft_strlen(s1) : 0;
	len += (s2 ? ft_strlen(s2) : 0);
	len++;
	if (!(ret = (char *)malloc(sizeof(char) * (len))))
		return (NULL);
	ft_bzero(ret, len);
	if (s1)
		ft_strcpy(ret, s1);
	if (s2)
		ft_strcat(ret, s2);
	return (ret);
}
