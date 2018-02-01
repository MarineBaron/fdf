/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 12:14:47 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/01 18:46:13 by mbaron           ###   ########.fr       */
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

int			get_next_word(char *s1, char *s2, int *index)
{
	int		i;
	int		j;

	i = *index;
	j = 0;
	if (!s1 || !s2)
		return (0);
	ft_strclr(s1);
	while (s2[i] && s2[i] == ' ')
		i++;
	while (s2[i] && s2[i] != ' ')
		s1[j++] = s2[i++];
	*index = i;
	return (1);
}
