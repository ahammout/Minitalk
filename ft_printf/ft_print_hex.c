/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:42:41 by ahammout          #+#    #+#             */
/*   Updated: 2021/12/31 18:50:53 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hex_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		num = num / 16;
		len++;
	}
	return (len);
}

void	ft_print_hex(unsigned int num, const char specifier)
{
	char	*hexa;

	if (specifier == 'x')
		hexa = "0123456789abcdef";
	if (specifier == 'X')
		hexa = "0123456789ABCDEF";
	if (num >= 16)
	{
		ft_print_hex(num / 16, specifier);
	}
	ft_printchar(hexa[num % 16]);
}

int	ft_hexa(unsigned int num, const char specifier)
{
	int	print_len;

	print_len = 0;
	if (num == 0)
		print_len += write(1, "0", 1);
	else
	{
		ft_print_hex(num, specifier);
		print_len += ft_hex_len(num);
	}
	return (print_len);
}
