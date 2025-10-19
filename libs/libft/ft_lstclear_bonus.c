/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:44:29 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/19 13:57:50 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear_bonus(t_list **lst, void (*del)(void*))
{
	t_list	*next_adr;

	while (*lst)
	{
		next_adr = (*lst)->next;
		ft_lstdelone_bonus(*lst, del);
		*lst = next_adr;
	}
	free (*lst);
	*lst = NULL;
}
