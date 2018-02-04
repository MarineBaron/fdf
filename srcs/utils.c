/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 12:14:47 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/04 19:21:20 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

static int	is_correct_arg(char *str)
{
	return (!ft_strcmp(str, "-f") || !ft_strcmp(str, "-m")
		|| !ft_strcmp(str, "-c"));
}

int			test_args(int argc, char *argv[])
{
	if ((argc != 1 && argc != 3 && argc != 5 && argc != 7) || (argc > 2
		&& !is_correct_arg(argv[1])) || (argc > 4 && (!is_correct_arg(argv[3])
		|| !ft_strcmp(argv[1], argv[3]))) || (argc > 6
		&& (!is_correct_arg(argv[5]) || !ft_strcmp(argv[1], argv[5])
		|| !ft_strcmp(argv[3], argv[5]))))
	{
		ft_putendl(FDF_USAGE);
		return (0);
	}
	return (1);
}

unsigned int	ft_atoi_hex(char *str)
{
	int				i;
	unsigned int	value;

	if (ft_strlen(str) != 8)
		return (0);
	value = 0;
	str += 8;
	i = -1;
	while (++i < 6)
	{
		value ^= (*str - (*str < 57 ? 48 : 55)) << i;
		str--;
	}
	return value;
}
