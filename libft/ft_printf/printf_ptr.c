/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-11 15:22:58 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-12-11 15:22:58 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	prnt_ptr(unsigned long p, char *hex, int fd);

int	printf_ptr(void *ptr, int fd)
{
	int		len;
	char	*hex;

	len = 0;
	hex = "0123456789abcdef";
	if (!ptr)
		return (printf_str("(nil)", fd));
	else
	{
		len += printf_str("0x", fd);
		len += prnt_ptr((unsigned long)ptr, hex, fd);
	}
	return (len);
}

static int	prnt_ptr(unsigned long p, char *hex, int fd)
{
	int	len;

	len = 0;
	if (p > 15)
	{
		len += prnt_ptr(p / 16, hex, fd);
		len += prnt_ptr(p % 16, hex, fd);
	}
	else
	{
		ft_putchar_fd(hex[p], fd);
		len++;
	}
	return (len);
}
