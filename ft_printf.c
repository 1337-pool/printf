/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaber <mjaber@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:55:49 by mjaber            #+#    #+#             */
/*   Updated: 2025/11/01 18:56:05 by mjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			if (*(format + 1) == 'c')
				count += ft_putchar(va_arg(args, int));
			else if (*(format + 1) == 's')
				count += ft_putstr(va_arg(args, char *));
			else if (*(format + 1) == 'p')
				count += ft_print_memory(va_arg(args, void *));
			else if (*(format + 1) == 'i' || *(format + 1) == 'd')
				count += ft_putnbr_base(va_arg(args, int), "0123456789");
			else if (*(format + 1) == 'u')
				count += ft_putunbr(va_arg(args, unsigned int));
			else if (*(format + 1) == 'x')
				count += ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef");
			else if (*(format + 1) == 'X')
				count += ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF");
			else if (*(format + 1) == '%')
				count += ft_putchar('%');
			format++;
		}
		else if (*format != '%')
			count += ft_putchar(*format);
		if (*format == '\0')
			break ;
		format++;
	}
	va_end(args);
	return (count);
}
