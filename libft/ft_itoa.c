/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-03 18:46:41 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-11-03 18:46:41 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	check_n_len(long int n);
static char		*n_to_str(long int n, char *str, long int len);

char	*ft_itoa(int n)
{
	char	*n_str;
	size_t	str_len;

	str_len = check_n_len(n);
	if (n == 0)
	{
		n_str = (char *) malloc (2);
		if (!n_str)
			return (NULL);
		n_str[0] = '0';
		n_str[1] = '\0';
		return (n_str);
	}
	n_str = (char *) malloc (str_len + 1);
	if (n_str == NULL)
		return (NULL);
	n_str = n_to_str(n, n_str, str_len);
	return (n_str);
}

static char	*n_to_str(long int n, char *str, long int len)
{
	size_t	i;

	i = len - 1;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	str[len] = '\0';
	return (str);
}

static size_t	check_n_len(long int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}
