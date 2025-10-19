/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:26:42 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/19 13:55:06 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast_bonus(t_list *lst)
{
	t_list	*buffer;

	if (!lst)
		return (NULL);
	buffer = lst;
	while (buffer->next)
		buffer = buffer->next;
	return (buffer);
}

// int main()
// {
// 	t_list * l =  NULL;
// 	ft_lstlast(l);
// 	return 0;
// }