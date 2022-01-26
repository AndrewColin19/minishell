/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:40:15 by lmataris          #+#    #+#             */
/*   Updated: 2022/01/26 11:28:33 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	select_cmd(t_cmd *cmd, int in, int out)
{
	if (check_cmd(cmd->cmd, ECHO, 1))
		cmd_echo(out, cmd->cmd);
	else if (check_cmd(cmd->cmd, PWD, 0))
		cmd_pwd(out, &g_env);
	else if (check_cmd(cmd->cmd, ENV, 0))
		cmd_env(out, g_env);
	else if (check_cmd(cmd->cmd, CD, 0))
		cmd_cd(&g_env, cmd->cmd);
	else if (check_cmd(cmd->cmd, EXPORT, 0))
		cmd_export(out, &g_env, cmd->cmd);
	else
		cmd_exec(cmd, in, out);
}

void	exec(t_cmd **cmds, int i, int in)
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
		select_cmd(cmds[i], in, pipes[1]);
		close(pipes[1]);
		if (redirect_out)
			write_redirection(pipes[0], redirect_out);
		if (cmds[i + 1])
			exec(cmds, i + 1, pipes[0]);
	}
	else
		select_cmd(cmds[i], in, 1);
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
			free_redirs(cmd[k]->cmds[i]->redirections[0]);
			free(cmd[k]->cmds[i]->redirections);
			free(cmd[k]->cmds[i]);
			i++;
		}
		free(cmd[k]->cmds);
		free(cmd[k]);
		k++;
	}
	free(cmd);
}
