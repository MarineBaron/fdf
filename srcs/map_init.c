/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:03:30 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/01 19:48:08 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		map_init_line(t_conf *conf, char *str, t_lstp *point);
{
	int		i;
	double	x;
	double	y;
	double	z;
	
	x = 0.0;
	y = (!point ? 0.0 : point->p->y + 1.0);
	i = 0;
	while(str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i])
		{
			if (!(ft_isdigit[i]))
				return (0);
				z = 0.0;
			map_add_point(x, y, get_number(line, &i, &z));
		}
	}
	return (1);
}
