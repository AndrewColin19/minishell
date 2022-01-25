/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:01:16 by acolin            #+#    #+#             */
/*   Updated: 2022/01/08 01:23:15 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	g_env = {0, 0, NULL};

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
	else
		cmd_exec(cmd, in, out);
}

void	exec(t_cmd **cmds, int i, int in)
{
	int 	pipes[2];
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

/*void	interrupt_signal(int signal)
{
	(void) signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	quit_signal(int signum)
{
	(void) signum;
	exit(0);
}*/

void 	free_lines(t_line **cmd)
{
	int 	i;
	int		k;
	int 	j;
	t_redir	*r;
	t_redir	*n;

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
			r = cmd[k]->cmds[i]->redirections[0];
			while (r)
			{
				n = r->next;
				free(r->kw);
				free(r);
				r = n;
			}
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

int	main(int argc, char *argv[], char **ev)
{
	char	*line;
	t_line	**lines;
	int 	i;

	(void) argc;
	(void) argv;
	init(ev, &g_env);
	//signal(SIGINT, interrupt_signal);
	//signal(11, quit_signal);
	while (1)
	{
		line = readline(SHELL_TEXT);
		add_history(line);
		if (line[0])
		{
			expend(&line);
			lines = parse(line);
			i = 0;
			while (lines[i])
			{
				exec(lines[i]->cmds, 0, 0);
				i++;
			}
			free_lines(lines);
		}
	}
}
