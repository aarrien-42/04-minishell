/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 09:25:38 by aarrien-          #+#    #+#             */
/*   Updated: 2022/09/22 11:47:00 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_chrs(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void	ft_convert(int n, int len, char *str)
{
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
	}
	else if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		ft_convert(147483648, len, str);
	}
	else
	{
		if (n < 0)
		{
			*str = '-';
			n *= -1;
		}
		while (n != 0)
		{
			str[len - 1] = (n % 10) + 48;
			n = n / 10;
			len--;
		}
	}
}

char	*ft_itoa(int n)
{
	char	*num;
	int		len;

	len = ft_chrs(n);
	num = malloc(len * sizeof(char) + 1);
	if (num == 0)
		return (NULL);
	ft_convert(n, len, num);
	return (num);
}
