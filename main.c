/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:48:53 by sade-ara          #+#    #+#             */
/*   Updated: 2025/10/03 16:25:19 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "headers/minishell.h"

int main (int argc, char **argv, char *envp[])
{
	if (argc != 1)
	{
		perror("Error: too many arguments.");
		exit(0);
		// nao deve execurta, pois primeiro deve entrar no shell
	}
	else
	{
		//inicia o shell
	}
	return (0);
}