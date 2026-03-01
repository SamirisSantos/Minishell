/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:59:01 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/03/01 20:28:47 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static long long	ft_atoll_overflow(int sign)
{
	errno = ERANGE;
	if (sign == 1)
		return (LLONG_MAX);
	return (LLONG_MIN);
}

static void	ft_atoll_sign(const char *nptr, int *i, int *sign)
{
	while ((nptr[*i] >= 9 && nptr[*i] <= 13) || nptr[*i] == 32)
		(*i)++;
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

long long	ft_atoll(const char *nptr)
{
	int				i;
	long long int	n;
	int				sign;

	i = 0;
	sign = 1;
	n = 0;
	if (ft_strncmp(nptr, "-9223372036854775808", 20) == 0)
		return (LLONG_MIN);
	ft_atoll_sign(nptr, &i, &sign);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (n > (LLONG_MAX - (nptr[i] - '0')) / 10)
			return (ft_atoll_overflow(sign));
		n = n * 10 + (nptr[i++] - '0');
	}
	return (n * sign);
}

// long long	ft_atoll(const char *nptr)
// {
// 	int				i;
// 	long long int	n;
// 	int				sign;

// 	i = 0;
// 	sign = 1;
// 	n = 0;
// 	if (ft_strncmp(nptr, "-9223372036854775808", 20) == 0)
// 		return (LLONG_MIN);
// 	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
// 	{
// 		i++;
// 	}
// 	if (nptr[i] == '-' || nptr[i] == '+')
// 	{
// 		if (nptr[i] == '-')
// 			sign *= -1;
// 		i++;
// 	}
// 	while (nptr[i] != '\0' && (nptr[i] >= '0' && nptr[i] <= '9'))
// 	{
// 		if (n > (LLONG_MAX - (nptr[i] - '0')) / 10)
// 			{
// 				errno = ERANGE;
// 				if (sign == 1)
// 					return (LLONG_MAX);
// 				return (LLONG_MIN);
// 			}
// 		n = n * 10 + (nptr[i] - '0');
// 		i++;
// 	}
// 	return (n * sign);
// }
