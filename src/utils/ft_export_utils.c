/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 18:23:18 by sade-ara          #+#    #+#             */
/*   Updated: 2026/02/26 18:23:18 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_print_export(t_shell *shell)
{
	int	i;
	int	k;

	i = 0;
	while (shell->envp_cpy[i])
	{
		k = 0;
		ft_printf (1, "declare -x ");
		while (shell->envp_cpy[i][k] && shell->envp_cpy[i][k] != '=')
			ft_printf (1, "%c", shell->envp_cpy[i][k++]);
		if (shell->envp_cpy[i][k] == '=')
			ft_printf (1, "=\"%s\"", &shell->envp_cpy[i][k + 1]);
		ft_printf (1, "\n");
		i++;
	}
}
