/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:21:20 by cpinho-c          #+#    #+#             */
/*   Updated: 2026/02/19 17:38:54 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	count_cmds(t_tree *temp, int *cmd_count)
{
	if (!temp)
		return ;
	if (temp->type == CMD)
		(*cmd_count)++;
	count_cmds(temp->left, cmd_count);
	count_cmds(temp->right, cmd_count);
}

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_truepath(char *cmd, char *fullpath)
{
	char		**splitpath;
	char		*truepath;
	char		*temp;
	int			i;

	splitpath = ft_split(fullpath, ':');
	i = 0;
	while (splitpath[i] && (cmd && cmd[0] != '\0'))
	{
		truepath = ft_strjoin(splitpath[i], "/");
		temp = truepath;
		truepath = ft_strjoin(temp, cmd);
		free(temp);
		if (access(truepath, F_OK) == 0)
		{
			free_array(splitpath);
			return (truepath);
		}
		free(truepath);
		i++;
	}
	free_array(splitpath);
	return (NULL);
}

char	*find_cmd_path(t_shell *shell, t_tree *tree)
{
	char	*fullpath;
	char	*cmd_path;

	if (is_builtin(tree))
		return (NULL);
	if (tree->data[0] == '/' || (tree->data[0] == '.' && tree->data[1] == '/'))
		return (ft_strdup(tree->data));
	fullpath = get_path(shell->envp_cpy);
	if (!fullpath)
		return (NULL);
	cmd_path = find_truepath(tree->data, fullpath);
	return (cmd_path);
}
