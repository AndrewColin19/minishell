/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:10:35 by lmataris          #+#    #+#             */
/*   Updated: 2022/01/26 12:10:26 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_redirect(t_redir **redir, int *in, int *out)
{
	t_redir	*r;

	r = *redir;
	while (r)
	{
		if (r->type == 0 || r->type == 1)
			*out = ft_create_file(r);
		else if (r->type == 2)
			*in = read_file(r);
		else if (r->type == 3)
			*in = heredoc(r);
		if (*in < 0 || *out < 0)
			return (0);
		r = r->next;
	}
	return (1);
}

int	ignore_quotes(char *cmd, int i)
{
	int		j;
	char	quote;

	quote = cmd[i];
	j = 1;
	while (cmd[i + j])
	{
		if (cmd[i + j] == quote && cmd[i + j - 1] != '\\')
			return (j);
		j++;
	}
	return (j);
}

int	get_type(char **cmd, int i)
{
	if (cmd[0][i] == '>' && cmd[0][i + 1] == '>')
		return (1);
	else if (cmd[0][i] == '>')
		return (0);
	else if (cmd[0][i] == '<' && cmd[0][i + 1] == '<')
		return (3);
	else
		return (2);
}

t_redir	*get_redirection(char **cmd, int i)
{
	t_redir	*redir;

	while (cmd[0][i])
	{
		if ((cmd[0][i] == '\'' || cmd[0][i] == '\"') && cmd[0][i - 1] != '\\')
			i += ignore_quotes(cmd[0], i);
		else if (cmd[0][i] == '>' || cmd[0][i] == '<')
		{
			redir = malloc(sizeof(t_redir));
			redir->type = get_type(cmd, i);
			redir->kw = get_kw(cmd[0], cmd[0][i]);
			delete_redirection(cmd, cmd[0][i]);
			redir->next = get_redirection(cmd, i);
			return (redir);
		}
		else
			i++;
	}
	return (NULL);
}
