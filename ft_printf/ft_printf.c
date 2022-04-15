/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:15:13 by ahammout          #+#    #+#             */
/*   Updated: 2021/12/31 19:26:21 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(char c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write (1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_specifier(va_list args, const char specifier)
{
	int	printchar_len;

	printchar_len = 0;
	if (specifier == 'c')
		printchar_len += ft_printchar(va_arg(args, int));
	else if (specifier == 's')
		printchar_len += ft_printstr(va_arg(args, char *));
	else if (specifier == '%')
		printchar_len += ft_printchar('%');
	else if (specifier == 'd' || specifier == 'i')
		printchar_len += ft_print_int_dec(va_arg(args, int));
	else if (specifier == 'u')
		printchar_len += ft_print_unsigned(va_arg(args, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		printchar_len += ft_hexa(va_arg(args, unsigned int), specifier);
	else if (specifier == 'p')
		printchar_len += ft_print_pointer(va_arg(args, unsigned long long));
	return (printchar_len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		printchar_len;
	va_list	args;

	i = 0;
	printchar_len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			printchar_len += ft_specifier(args, str[i + 1]);
			i++;
		}
		else
			printchar_len += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (printchar_len);
}
