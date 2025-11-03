/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaber <mjaber@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:51:28 by mjaber            #+#    #+#             */
/*   Updated: 2025/11/03 13:53:06 by mjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_print_memory(void *p);
int	ft_putchar(char c);
int	ft_putnbr_base(long long nbr, char *base);
int	ft_putstr(char *str);
int	ft_strlen(char *str);
int	ft_printf(const char *format, ...);
int	ft_putunbr(unsigned int nbr);

#endif
