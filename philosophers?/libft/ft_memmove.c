/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:16:03 by abkhefif          #+#    #+#             */
/*   Updated: 2024/12/10 14:12:58 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*tdst;
	const unsigned char	*tsrc;

	if (!dst || !src)
		return (NULL);
	tdst = (unsigned char *) dst;
	tsrc = (const unsigned char *) src;
	if (dst == src)
		return (dst);
	if (dst > src)
	{
		while (n--)
			tdst[n] = tsrc[n];
	}
	else if (dst < src)
	{
		while (n--)
			*tdst++ = *tsrc++;
	}
	return (dst);
}
