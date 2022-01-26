/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:40:15 by lmataris          #+#    #+#             */
/*   Updated: 2022/01/26 18:20:01 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	select_cmd(t_cmd *cmd, int in, int out, t_line **lines)
{
	if (!ft_strcmp(ECHO, cmd->kw))
		cmd_echo(out, cmd);
	else if (!ft_strcmp(PWD, cmd->kw))
		cmd_pwd(out);
	else if (!ft_strcmp(ENV, cmd->kw))
		cmd_env(out);
	else if (!ft_strcmp(CD, cmd->kw))
		cmd_cd(cmd);
	else if (!ft_strcmp(EXPORT, cmd->kw))
		cmd_export(out, cmd);
	else if (!ft_strcmp(UNSET, cmd->kw))
		cmd_unset(cmd);
	else if (!ft_strcmp(EXIT, cmd->kw))
		cmd_exit(lines);
	else
		cmd_exec(cmd, in, out);
}

void	exec(t_cmd **cmds, int i, int in, t_line **lines)
{
	int		pipes[2];
	int		redirect_out;
	int		redirect_in;

	pipe(pipes);
	redirect_out = 0;
	redirect_in = 0;
	get_redirect(cmds[i]->redirections, &redirect_in, &redirect_out);
	if (redirect_in)
		in = redirect_in;
	if (cmds[i + 1] || redirect_out)
	{
		select_cmd(cmds[i], in, pipes[1], lines);
		close(pipes[1]);
		if (redirect_out)
			write_redirection(pipes[0], redirect_out);
		if (cmds[i + 1])
			exec(cmds, i + 1, pipes[0], lines);
	}
	else
		select_cmd(cmds[i], in, 1, lines);
}

void	free_redirs(t_redir *r)
{
	t_redir	*n;

	while (r)
	{
		n = r->next;
		free(r->kw);
		free(r);
		r = n;
	}
}

void	free_lines(t_line **cmd)
{
	int		i;
	int		k;
	int		j;

	k = 0;
	while (cmd[k])
	{
		free(cmd[k]->line);
		i = 0;
		while (cmd[k]->cmds[i])
		{
			free(cmd[k]->cmds[i]->cmd);
			j = 0;
			while (cmd[k]->cmds[i]->args[j])
				free(cmd[k]->cmds[i]->args[j++]);
			free(cmd[k]->cmds[i]->args);
			free_redirs(cmd[k]->cmds[i]->redirections[0]);
			free(cmd[k]->cmds[i]->redirections);
			free(cmd[k]->cmds[i++]);
		}
		free(cmd[k]->cmds);
		free(cmd[k]);
		k++;
	}
	free(cmd);
}
