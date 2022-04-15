/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:42:50 by ahammout          #+#    #+#             */
/*   Updated: 2021/12/31 19:18:44 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptr_len(unsigned long long num)
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

void	ft_print_ulptr(unsigned long long ptr)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (ptr >= 16)
	{
		ft_print_ulptr(ptr / 16);
	}
	ft_printchar(hexa[ptr % 16]);
}

int	ft_print_pointer(unsigned long long ptr)
{
	int	len;

	len = 0;
	len += write (1, "0x", 2);
	if (ptr == 0)
		len += write (1, "0", 1);
	else
	{
		ft_print_ulptr(ptr);
		len += ft_ptr_len(ptr);
	}
	return (len);
}
