/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:18:13 by abkhefif          #+#    #+#             */
/*   Updated: 2024/12/14 09:32:30 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char s, char c)
{
	if (c == s)
		return (1);
	return (0);
}

int	count_words(const char *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && check(s[i], c))
			i++;
		if (s[i])
		{
			words++;
			while (s[i] && !check(s[i], c))
				i++;
		}
	}
	return (words);
}

int	len_word(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && !check(s[i], c))
		i++;
	return (i);
}

static char	*ft_strdup_len(const char *s, int len)
{
	char	*dest;
	int		i;

	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		i;
	int		index;

	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!s || !dest)
		return (NULL);
	i = 0;
	index = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			dest[index++] = ft_strdup_len(&s[i], len_word(&s[i], c));
			i += len_word(&s[i], c);
		}
		else
			i++;
	}
	dest[index] = NULL;
	return (dest);
}
