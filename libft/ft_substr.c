/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-31 17:15:22 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-10-31 17:15:22 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	r_len;

	if (s == NULL)
		return (NULL);
	r_len = ft_strlen(s);
	if (start >= r_len)
	{
		sub = (char *) malloc(1);
		if (sub == NULL)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	r_len = r_len - start;
	if (len < r_len)
		r_len = len;
	sub = (char *)malloc(r_len + 1);
	if (sub == NULL)
		return (NULL);
	ft_memcpy(sub, &s[start], r_len);
	sub[r_len] = '\0';
	return (sub);
}
