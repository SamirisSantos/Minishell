/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-12 12:07:37 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-12-12 12:07:37 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	printf_str(char *str, int fd)
{
	if (!str)
		return (printf_str("(null)", fd));
	ft_putstr_fd(str, fd);
	return (ft_strlen(str));
}
