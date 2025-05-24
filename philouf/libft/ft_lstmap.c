/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhefif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:45:26 by abkhefif          #+#    #+#             */
/*   Updated: 2024/12/14 11:16:33 by abkhefif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;
	t_list	*courrant;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	courrant = lst;
	while (courrant)
	{
		temp = ft_lstnew(f(courrant->content));
		if (!temp)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, temp);
		courrant = courrant -> next;
	}
	return (new);
}
