/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:48:53 by sade-ara          #+#    #+#             */
/*   Updated: 2025/11/18 16:41:52 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int main (int argc, char **argv, char *envp[])
{
	if (argc != 1)
	{
		ft_printf(STDERR_FILENO,"Error: too many arguments.\n");
		exit(0);
	}
	else
	{
		//inicia o shell
	}
	return (0);
}