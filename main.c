/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:48:53 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/19 14:13:18 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int	main(int argc, char **argv, char *envp[])
{
	t_shell	*shell;

	if (argc != 1)
	{
		ft_printf(STDERR_FILENO,"Error: too many arguments.\n");
		exit(0);
	}
	else
	{
		*init_shell();
		init_signals();
		shell_control(shell); //doing em src ...
		free_shell(shell);
	}
	return (EXIT_SUCCESS);
}
