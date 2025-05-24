/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:45:46 by abkhefif          #+#    #+#             */
/*   Updated: 2024/12/10 16:07:20 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	totlen;
	size_t	i;
	char	*dest;

	if (!s)
		return (NULL);
	totlen = ft_strlen(s);
	i = 0;
	if (start >= totlen)
		return (ft_calloc(1, 1));
	if (len > totlen - start)
		len = totlen - start;
	dest = malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
