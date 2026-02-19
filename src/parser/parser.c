/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sade-ara <sade-ara@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:15:13 by sade-ara          #+#    #+#             */
/*   Updated: 2026/01/28 17:00:56 by sade-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == CMD || token->type == CMD_ARG)
			count++;
		token = token->next;
	}
	return (count);
}

t_token	*handle_redirects(t_token *token, t_cmd *cmd)
{
	if (token->type == REDIR_IN || token->type == HEREDOC)
	{
		if (cmd->input_file)
			free(cmd->input_file);
		cmd->input_file = ft_strdup(token->next->data);
		if (token->type == HEREDOC)
			cmd->heredoc = 1;
		else
			cmd->heredoc = 0;
	}
	else if (token->type == REDIR_OUT || token->type == APPEND)
	{
		if (cmd->output_file)
			free(cmd->output_file);
		cmd->output_file = ft_strdup(token->next->data);
		if (token->type == APPEND)
			cmd->append = 1;
		else
			cmd->append = 0;
	}
	return (token->next);
}

static void	fill_cmd(t_cmd *new, t_token **token)
{
	int	i;

	i = 0;
	new->args = malloc(sizeof(char *) * (count_args(*token) + 1));
	if (!new->args)
		return ;
	while (*token && (*token)->type != PIPE)
	{
		if ((*token)->type == CMD || (*token)->type == CMD_ARG)
		{
			new->args[i++] = ft_strdup((*token)->data);
			*token = (*token)->next;
		}
		else if ((*token)->type >= REDIR_IN && (*token)->type <= HEREDOC)
		{
			*token = handle_redirects(*token, new);
		}
	}
	new->args[i] = NULL;
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*new;

	head = NULL;
	current = NULL;
	while (tokens)
	{
		new = init_cmd();
		if (!new)
		{
			free_cmd(new);
			return (NULL);
		}
		fill_cmd(new, &tokens);
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (head);
}
