/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:21:39 by abkhefif          #+#    #+#             */
/*   Updated: 2024/12/14 09:32:46 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(long n)
{
	int	tot;

	tot = 0;
	if (n < 0)
	{
		n *= -1;
		tot++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		tot++;
	}
	return (tot);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		i;
	long	nb;

	nb = n;
	i = check(nb);
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	dest[i--] = '\0';
	if (nb == 0)
		return (dest[0] = '0', dest);
	if (nb < 0)
	{
		dest[0] = '-';
		nb = -nb;
	}
	while (nb)
	{
		dest[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (dest);
}
