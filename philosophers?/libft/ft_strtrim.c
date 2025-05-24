/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:01:30 by abkhefif          #+#    #+#             */
/*   Updated: 2024/12/14 09:32:08 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char s1, const char *set)
{
	while (*set)
	{
		if (s1 == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	start = 0;
	while (s1[i] && check(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && check(s1[end - 1], set))
		end--;
	dest = malloc(sizeof(char) * (end - start + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (start < end)
		dest[i++] = s1[start++];
	dest[i] = '\0';
	return (dest);
}
