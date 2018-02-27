/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 12:14:47 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/26 08:58:46 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "config.h"

static int		is_correct_arg(char *str)
{
	return (!ft_strcmp(str, "-f") || !ft_strcmp(str, "-m")
		|| !ft_strcmp(str, "-c"));
}

int				test_args(int argc, char *argv[])
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

int				get_grad_col(int co, int cd, double p)
{
	if (co == cd)
		return (co);
	return ((int)((double)co + ((double)cd - (double)(co)) * p));
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
	return (value);
}

void			fill_rect(t_img *img, t_rect *rect)
{
	int		i;
	int		j;
	char	*ptr;

	ptr = img->ptr;
	i = -1;
	while (++i < rect->h)
	{
		ptr = img->ptr + (((rect->y + i) * img->sl) + rect->x * img->bpp);
		j = -1;
		while (++j < rect->w)
		{
			ft_memcpy(ptr, (void *)&rect->c_bg, img->bpp);
			ptr += img->bpp;
		}
	}
}

void			*init_pointer(size_t size, char *str_error)
{
	void *p;

	p = NULL;
	if (!(p = ft_memalloc(size)))
		set_error(str_error, 1);
	return (p);
}
