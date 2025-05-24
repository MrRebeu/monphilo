/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:57:22 by abkhefif          #+#    #+#             */
/*   Updated: 2024/12/16 16:07:34 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	if (count == 18446744073709551615UL && size == 18446744073709551615UL)
		return (NULL);
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	while (i < size * count)
		tmp[i++] = 0;
	return ((void *) tmp);
}
