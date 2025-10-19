/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:49 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/17 15:20:20 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h> TESTING PURPOSES

int	ft_atoi(const char *nptr)
{
	const char	*str;
	int			store;
	int			sign;
	int			i;

	str = nptr;
	store = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str [i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] != 0 && str[i] >= '0' && str[i] <= '9')
	{
		store = store * 10 + (str[i] - '0');
		i++;
	}
	return (sign * store);
}

// int main()
// {
// 	const char *teststring1 = "-123456789";
// 	const char *teststring2 = "-2147483648";
// 	int result1 = ft_atoi(teststring1);
// 	int result2 = ft_atoi(teststring2);
// 	int libresult1 = atoi(teststring1);
// 	int libresult2 = atoi(teststring2);
// printf("My  atoi general test:  
// %d Memory Address test: %p\n", result1, (void *)&result1);
// printf("Lib atoi general test:  
// %d Memory Address test: %p\n", libresult1, (void *)&libresult1);
// printf("My  atoi int_min test:  
// %d Memory Address test: %p\n", result2, (void *)&result2);
// printf("Lib atoi int_min test:  
// %d Memory Address test: %p\n", libresult2, (void *)&libresult2);
// 	return 0;
// }
//		TESTED AND WORKS + NORM COMPLIANT
