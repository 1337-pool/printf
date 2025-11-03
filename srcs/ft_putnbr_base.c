/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaber <mjaber@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:37:03 by mjaber            #+#    #+#             */
/*   Updated: 2025/11/03 14:02:47 by mjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_base(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(str) <= 1)
		return (0);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '+' || str[i] == '-')
			break ;
		j = i + 1;
		while (str[j])
		{
			if (str[i] == str[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_putunbr(unsigned int nbr)
{
	unsigned int	count;

	count = 0;
	if (!nbr)
	{
		write(1, "0", 1);
		return (1);
	}
	if (nbr >= 10)
		count += ft_putunbr(nbr / 10);
	ft_putchar(nbr % 10 + '0');
	count++;
	return (count);
}

int	ft_putnbr_base(long long nbr, char *base)
{
	int	base_len;
	int	count;

	count = 0;
	if (!ft_check_base(base))
		return (0);
	base_len = ft_strlen(base);
	if (nbr < 0)
	{
		ft_putchar('-');
		count++;
		nbr = -nbr;
	}
	if (nbr >= base_len)
		count += ft_putnbr_base(nbr / base_len, base);
	ft_putchar(base[nbr % base_len]);
	count++;
	return (count);
}
