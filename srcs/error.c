/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:47:23 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/01 16:26:27 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		set_error(char *str, int ex)
{
	if (ft_strlen(str))
		ft_putendl(str);
	perror(strerror(errno));
	if (ex)
		exit(EXIT_FAILURE);
	return (0);
}
