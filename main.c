/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:48:53 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/19 17:46:03 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int	g_sig;

int	main(int argc, char **argv, char *envp[])
{
	t_shell	*shell;

	(void)argv;
	if (argc != 1)
	{
		ft_printf(STDERR_FILENO,"Error: too many arguments.\n");
		exit(0);
	}
	else
	{
		shell = init_shell();
		shell->envp_cpy = copy_envp(shell, envp);
		shell_control(shell);
		free_shell(shell);
	}
	return (EXIT_SUCCESS);
}
