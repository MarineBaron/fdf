/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitdel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 08:07:39 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/03 15:17:53 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_strsplitdel(char **str)
{
	int		i;

	if (!str)
		return ;
	i = -1;
	while(str[++i])
		ft_strdel(&(str[i]));
	free(str);
	str = NULL;
}