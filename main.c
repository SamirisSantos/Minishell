/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:48:53 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/13 18:12:00 by sade-ara         ###   ########.fr       */
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
		*init_shell();//TODO
		init_signals(); //TODO esta em utils/init.c
		shell_control(shell); //doing em src ...
		free_shell(shell); //TODO esta em utils/utils.c
	}
	return (EXIT_SUCCESS);
}
