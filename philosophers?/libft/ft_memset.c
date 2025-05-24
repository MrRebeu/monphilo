/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:20:22 by abkhefif          #+#    #+#             */
/*   Updated: 2024/12/10 09:53:57 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*src, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) src;
	while (len--)
		*ptr++ = (unsigned char) c;
	return (src);
}
