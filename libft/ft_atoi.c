/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:30:36 by mbaron            #+#    #+#             */
/*   Updated: 2017/12/21 14:43:23 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	mba_atoi_limits(long long int nb, int neg, char c)
{
	long long int	mi;

	mi = 922337203685477580;
	if (neg == 1 && (nb > mi || (nb == mi && c > '7')))
		return (-1);
	else if (neg == -1 && (nb > mi || (nb == mi && c > '8')))
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	long long int	nb;
	int				i;
	int				neg;
	int				max;
	int				exit_limit;

	nb = 0;
	i = 0;
	max = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	neg = (str[i] == '-' ? -1 : 1);
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (max && (exit_limit = mba_atoi_limits(nb, neg, str[i])))
			return (exit_limit == 1 ? 0 : -1);
		nb = nb * 10 + str[i] - 48;
		max = (nb >= 922337203685477580) ? 1 : 0;
		i++;
	}
	return (neg * (int)nb);
}
