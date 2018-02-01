/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 09:43:44 by mbaron            #+#    #+#             */
/*   Updated: 2017/12/21 09:17:56 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	mba_count_letters(char const *s, char c, size_t index)
{
	size_t	n;

	n = 0;
	while (s[index] && s[index] != c)
	{
		index++;
		n++;
	}
	return (n);
}

static size_t	mba_count_words(char const *s, char c)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = 0;
	if (!s)
		return (0);
	if (!c)
		return (1);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			n++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (n);
}

static char		**mba_free_tab(char **tab, size_t index)
{
	while (index--)
		free(tab[index]);
	free(tab);
	return (NULL);
}

static char		*mba_create_word(char const *s, char c, size_t index)
{
	char	*word;
	size_t	i;

	if (!(word = (char *)malloc(sizeof(char)
					* mba_count_letters(s, c, index) + 1)))
		return (NULL);
	i = 0;
	while (s[index] && s[index] != c)
		word[i++] = s[index++];
	word[i] = '\0';
	return (word);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	nb_words;
	size_t	i;
	size_t	j;

	nb_words = mba_count_words(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_words + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s && s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			if (!(tab[j] = mba_create_word(s, c, i)))
				return (mba_free_tab(tab, j));
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	tab[j] = NULL;
	return (tab);
}
