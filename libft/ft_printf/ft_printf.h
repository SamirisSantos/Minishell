/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-12 12:04:48 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-12-12 12:04:48 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "../libft.h"

int	ft_printf(int fd, const char *mand, ...);
int	printf_char(char c, int fd);
int	printf_str(char *str, int fd);
int	printf_digits(int n, int fd);
int	printf_uns(unsigned int n, int fd);
int	printf_hex(unsigned int n, int state, int fd);
int	printf_ptr(void *ptr, int fd);

#endif