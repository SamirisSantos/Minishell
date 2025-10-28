/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:09:11 by sade-ara          #+#    #+#             */
/*   Updated: 2025/10/28 16:23:11 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// change variable to receive struct later 
void	ft_echo(t_shell *shell)
{
	int		i;
	bool	withN;
	int		fd;

	i = 0;
	withN = false;
	////////FIIIIIIX
	while (args[i] && (ft_strncmp(args[i], "-n", 2) == 0) 
		&& (ft_strlen(args[i]) == 2))
	{
		i++;
		withN = true;
	}
	while (args[i])
	{
		ft_printf(fd, "%s", args[i]);
		i++;
		if (args[i])
			ft_printf(fd, " ");
	}
	if (!withN)
		ft_printf(fd, "\n");
}

// int main (int ac, char **av)
// {
// 	(void)ac;
// 	ft_echo(av + 2, 1);
// }
