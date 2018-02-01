/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 10:33:44 by mbaron            #+#    #+#             */
/*   Updated: 2017/12/21 16:21:42 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	mba_abs(int n)
{
	return (n < 0 ? -n : n);
}

static char	*mba_get_tab(int n, int *d)
{
	char			*tab;
	unsigned int	l;

	l = n < 0 ? 3 : 2;
	*d = 1;
	while (n > 9 || n < -9)
	{
		n /= 10;
		*d *= 10;
		l++;
	}
	if (!(tab = (char*)malloc(sizeof(char) * l)))
		return (NULL);
	return (tab);
}

char		*ft_itoa(int n)
{
	char			*tab;
	unsigned int	i;
	int				d;

	d = 1;
	if (!(tab = mba_get_tab(n, &d)))
		return (NULL);
	i = 0;
	if (n < 0)
	{
		tab[i] = '-';
		i++;
	}
	while (d > 1)
	{
		tab[i] = mba_abs(n / d) + 48;
		n %= d;
		d /= 10;
		i++;
	}
	tab[i] = mba_abs(n) + 48;
	i++;
	tab[i] = '\0';
	return (tab);
}
