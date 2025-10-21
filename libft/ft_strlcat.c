/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-31 13:14:07 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-10-31 13:14:07 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (s_len);
	if (d_len >= size)
		return (size + s_len);
	while ((d_len + i) < (size - 1) && src[i] != '\0')
	{
		dst[d_len + i] = src[i];
		i++;
	}
	if (d_len + i < size)
		dst[d_len + i] = '\0';
	return (d_len + s_len);
}
