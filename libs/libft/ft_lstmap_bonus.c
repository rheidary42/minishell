/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:11:14 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/19 13:58:23 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap_bonus(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*lst_cont;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		lst_cont = ft_lstnew_bonus(f(lst->content));
		if (!lst_cont)
			return (ft_lstclear_bonus(&new_lst, del), NULL);
		ft_lstadd_back_bonus(&new_lst, lst_cont);
		lst = lst->next;
	}
	return (new_lst);
}
