/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:04:10 by abkhefif          #+#    #+#             */
/*   Updated: 2024/12/10 10:27:53 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ts1;
	const unsigned char	*ts2;

	ts1 = (const unsigned char *)s1;
	ts2 = (const unsigned char *)s2;
	while (n--)
	{
		if (*ts1 != *ts2)
			return (*ts1 - *ts2);
		ts1++;
		ts2++;
	}
	return (0);
}
