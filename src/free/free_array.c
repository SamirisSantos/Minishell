/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:40:39 by sade-ara          #+#    #+#             */
/*   Updated: 2026/03/02 15:26:37 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	if (!array[i] && array[i + 1])
		i++;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
