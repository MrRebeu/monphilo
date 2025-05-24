/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:53:07 by abkhefif          #+#    #+#             */
/*   Updated: 2024/12/10 10:28:11 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*d;

	d = (const unsigned char *) s;
	while (n--)
	{
		if (*d == (unsigned char)c)
			return ((void *)d);
		d++;
	}
	return (0);
}
