/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:48:53 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/17 14:24:35 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

/*
readline() → lexer(tokenrização) → parser → executor
*/

int	main(int argc, char **argv, char *envp[])
{
	t_shell	*shell;

	if (argc != 1)
	{
		perror("Error: too many arguments.");
		exit(0);
		// nao deve executar, pois primeiro deve entrar no shell
	}
	else
	{
		*init_shell();
		init_signals(); //TODO 
		shell_control(shell); //doing em src ...
		free_shell(shell);
	}
	return (EXIT_SUCCESS);
}
