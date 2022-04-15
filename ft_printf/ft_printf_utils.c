/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:42:24 by ahammout          #+#    #+#             */
/*   Updated: 2021/12/31 19:32:59 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_int_len(int num)
{
	int	len;

	len = 0;
	if (num <= 0)
	{
		len ++;
		num = -num;
	}
	while (num != 0)
	{
		len ++;
		num = num / 10;
	}
	return (len);
}

int	ft_print_int_dec(int n)
{
	long	num;

	num = n;
	if (num < 0)
	{
		num = -num;
		ft_printchar('-');
	}
	if (num <= 9)
	{
		ft_printchar(num + 48);
	}
	if (num > 9)
	{
		ft_print_int_dec(num / 10);
		ft_printchar(num % 10 + 48);
	}
	return (ft_int_len(n));
}

int	ft_uint_len(unsigned int num)
{
	unsigned int	len;

	len = 0;
	if (num == 0)
		len ++;
	while (num != 0)
	{
		len ++;
		num = num / 10;
	}
	return (len);
}

int	ft_print_unsigned(unsigned int n)
{
	if (n <= 9)
	{
		ft_printchar(n + 48);
	}
	if (n > 9)
	{
		ft_print_unsigned(n / 10);
		ft_printchar(n % 10 + 48);
	}
	return (ft_uint_len(n));
}
