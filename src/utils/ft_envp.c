/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:02:29 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/01/20 16:02:28 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**copy_envp(t_shell *shell, char *envp[])
{
	char	**temp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	temp = (char **)malloc((i + 1) * sizeof(char *));
	if (!temp)
	{
		shell->exit_status = 12;
		ft_printf(STDERR_FILENO, "malloc: %s", strerror(errno));
		return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		temp[i] = ft_strdup(envp[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

// int main(int ac, char **av, char *envp[])
// {
// 	(void)ac;
// 	(void)av;
// 	char **envp_cpy = copy_envp(envp);
// 	int i = 0;
// 	while (envp_cpy[i])
// 	{
// 		ft_printf(1, "%s\n", envp_cpy[i]);
// 		i++;
// 	}
// }