/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:26:54 by abkhefif          #+#    #+#             */
/*   Updated: 2024/12/10 10:32:00 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*tdest;
	const unsigned char	*tsrc;

	tdest = (unsigned char *) dest;
	tsrc = (const unsigned char *) src;
	while (n--)
		*tdest++ = *tsrc++;
	return (dest);
}
