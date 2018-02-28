/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 12:14:47 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/28 20:37:08 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				is_correct_arg(char *str)
{
	return (!ft_strcmp(str, "-f") || !ft_strcmp(str, "-m")
		|| !ft_strcmp(str, "-c"));
}

unsigned int	ft_atoi_hex(char *str)
{
	int				i;
	unsigned int	value;

	if (ft_strlen(str) != 8)
		return (0);
	value = 0;
	i = 1;
	while (++i < 8)
		value ^= (str[i] - (str[i] < 57 ? 48 : 55)) << ((7 - i) * 4);
	return (value);
}

void			*init_pointer(t_conf *conf, size_t size, char *str_error)
{
	void *p;

	p = NULL;
	if (!(p = ft_memalloc(size)))
		set_error(conf, str_error, 1);
	return (p);
}

void			copy_control(t_conf *conf)
{
	if (!conf->control->n)
		conf->control->n = (t_values *)init_pointer(conf,
			sizeof(t_values), "ErrM (conf->control->n)");
	ft_memcpy(conf->control->n, conf->control->v, sizeof(t_values));
}

int				set_error(t_conf *conf, char *str, int ex)
{
	if (ft_strlen(str))
		ft_putendl(str);
	perror(strerror(errno));
	if (ex)
	{
		if (conf)
			destroy(conf);
		exit(EXIT_FAILURE);
	}
	return (0);
}
