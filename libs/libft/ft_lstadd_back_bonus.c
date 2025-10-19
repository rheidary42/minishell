/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:41:19 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/19 13:57:17 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back_bonus(t_list **lst, t_list *new)
{
	t_list	*new_lst;

	if (*lst == NULL)
		*lst = new;
	else
	{
		new_lst = ft_lstlast_bonus(*lst);
		new_lst->next = new;
	}
}

// int main()
// {
// 	t_list *l =  NULL;
// 	ft_lstadd_back(&l, ft_lstnew((void*)1));
// 	return 0;
// }