/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-23 10:39:15 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-10-23 10:39:15 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	sign;

	i = 0;
	sign = 1;
	n = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
	{
		i++;
	}
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] != '\0')
	{
		if (!(nptr[i] >= '0' && nptr[i] <= '9'))
			break ;
		n = n * 10 + (nptr[i] - '0');
		i++;
	}
	return (n * sign);
}
