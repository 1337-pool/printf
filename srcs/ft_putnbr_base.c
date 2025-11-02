/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaber <mjaber@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:37:03 by mjaber            #+#    #+#             */
/*   Updated: 2025/11/02 09:58:43 by mjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

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

int ft_putunbr(int nbr)
{
  long n;
  unsigned int  count;

  count = 0;
  if (!nbr)
    return (0);
  n = nbr;
  if (n < 0)
    n += 4294967296;
  if (n >= 10)
    count += ft_putunbr(n / 10);
  ft_putchar(n % 10 + '0');
  count++;
  return (count);
}

int	ft_putnbr_base(int nbr, char *base)
{
	long	n;
	int		base_len;
  int count;

  count = 0;
	if (!ft_check_base(base))
		return (0);
	base_len = ft_strlen(base);
	n = nbr;
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= base_len)
		count += ft_putnbr_base(n / base_len, base);
	ft_putchar(base[n % base_len]);
  count++;
  return (count);
}
