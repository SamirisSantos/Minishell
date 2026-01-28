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

int	g_sig;

int	main(int argc, char **argv, char *envp[])
{
	t_shell	*shell;
	char	*input;

	if (argc != 1)
	{
		ft_printf(STDERR_FILENO,"Error: too many arguments.\n");
		exit(0);
	}
	else
	{
		shell = init_shell();
		shell_control(shell, input); //doing em src ...
	}
	return (EXIT_SUCCESS);
}
