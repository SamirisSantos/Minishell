/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 10:09:33 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-10-29 10:09:33 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	d = (char *) dest;
	s = (char *) src;
	i = 0;
	if (d == NULL && s == NULL)
		return (NULL);
	if (d > s)
	{
		while (n-- > 0)
		{
			d[n] = s[n];
		}
		return (dest);
	}
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
