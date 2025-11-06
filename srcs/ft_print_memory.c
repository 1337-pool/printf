/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaber <mjaber@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 09:51:50 by mjaber            #+#    #+#             */
/*   Updated: 2025/11/03 13:59:33 by mjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_puthex(unsigned long a, char *buf, char *hex, int *i)
{
	int	len;

	len = 0;
	if (a == 0)
		buf[(*i)--] = '0';
	else
	{
		while (a > 0)
		{
			buf[(*i)--] = hex[a & 0xF];
			a >>= 4;
			len++;
		}
	}
	return (len);
}

int	ft_print_memory(void *p)
{
	unsigned long	a;
	char			buf[32];
	int				i;
	int				len;
	char			*hex;

	if (!p)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	i = 31;
	a = (unsigned long)p;
	hex = "0123456789abcdef";
	len = ft_puthex(a, buf, hex, &i);
	buf[i--] = 'x';
	buf[i--] = '0';
	len += 2;
	write(1, buf + i + 1, 31 - i);
	return (len);
}
