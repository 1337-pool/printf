/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaber <mjaber@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 10:53:34 by mjaber            #+#    #+#             */
/*   Updated: 2025/11/01 10:53:39 by mjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef   PRINTF_H
# define PRINTF_H

#include <stdarg.h>
#include <unistd.h>

int	ft_print_memory(void *p);
int	ft_putchar(char c);
int	ft_putnbr_base(long long nbr, char *base);
int	ft_putstr(char *str);
int	ft_strlen(char *str);
int ft_printf(const char *format, ...);
int ft_putunbr(unsigned int nbr);

#endif
