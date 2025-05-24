/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:36:57 by abkhefif          #+#    #+#             */
/*   Updated: 2024/12/14 11:17:03 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*temp;

	if (!lst)
		return (0);
	i = 1;
	temp = lst;
	while (temp->next)
	{
		temp = temp -> next;
		i++;
	}
	return (i);
}
